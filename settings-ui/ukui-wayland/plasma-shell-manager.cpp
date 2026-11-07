/*
 * Peony-Qt
 *
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#include "plasma-shell-manager.h"
#include "plasma-shell-client-protocol.h"
#include "plasma-window-management-client-protocol.h"

#include <QApplication>
#include <qpa/qplatformnativeinterface.h>
#include <wayland-client.h>
#include <unistd.h>

static PlasmaShellManager* global_instance = nullptr;

PlasmaShellManager *PlasmaShellManager::getInstance()
{
    if (!global_instance)
        global_instance = new PlasmaShellManager;
    return global_instance;
}

/* ------------------------------------------------------------------ */
/* Wayland state                                                       */
/* ------------------------------------------------------------------ */

static wl_display *display = nullptr;
static wl_registry *registry = nullptr;
static wl_shell *shell = nullptr;
static org_kde_plasma_shell *plasmaShell = nullptr;
static org_kde_plasma_window_management *windowManagement = nullptr;
/* Highest protocol version we bind, enough for window_with_uuid. */
static constexpr uint32_t kWindowManagementBindVersion = 13;
static constexpr uint32_t kPlasmaShellBindVersion = 8;

struct PlasmaWindowState
{
    org_kde_plasma_window *obj = nullptr;
    quint32 pid = 0;
    QString appId;
    bool keepAbove = false;
};

/* The single application window, matched by app id. */
static PlasmaWindowState *appWindow = nullptr;
static bool isFirstCreate = true;

static wl_display *waylandDisplayFromApplication()
{
    if (qGuiApp && qGuiApp->platformNativeInterface()) {
        const QByteArray resources[] = {
            QByteArrayLiteral("display"),
            QByteArrayLiteral("wl_display")
        };
        for (const QByteArray &resource : resources) {
            auto *d = reinterpret_cast<wl_display *>(
                qGuiApp->platformNativeInterface()->nativeResourceForIntegration(resource));
            if (d)
                return d;
        }
    }
    // Fall back to a dedicated connection to the default compositor socket.
    return wl_display_connect(nullptr);
}

static wl_surface *surfaceForWindow(QWindow *window)
{
    if (!qGuiApp || !qGuiApp->platformNativeInterface())
        return nullptr;
    return reinterpret_cast<wl_surface *>(
        qGuiApp->platformNativeInterface()->nativeResourceForWindow(QByteArrayLiteral("surface"), window));
}

/* ------------------------------------------------------------------ */
/* org_kde_plasma_window listener                                      */
/* ------------------------------------------------------------------ */

static void window_handle_app_id_changed(void *data, org_kde_plasma_window *, const char *app_id)
{
    auto *state = static_cast<PlasmaWindowState*>(data);
    state->appId = QString::fromUtf8(app_id);
    if (isFirstCreate && state->appId == QApplication::applicationName()) {
        isFirstCreate = false;
        appWindow = state;
    }
}

static void window_handle_title_changed(void *data, org_kde_plasma_window *, const char *title)
{
    Q_UNUSED(data);
    Q_UNUSED(title);
}

static void window_handle_state_changed(void *data, org_kde_plasma_window *, uint32_t flags)
{
    auto *state = static_cast<PlasmaWindowState*>(data);
    state->keepAbove = flags & ORG_KDE_PLASMA_WINDOW_MANAGEMENT_STATE_KEEP_ABOVE;
}

static void window_handle_unmapped(void *data, org_kde_plasma_window *)
{
    auto *state = static_cast<PlasmaWindowState*>(data);
    if (appWindow == state)
        appWindow = nullptr;
    org_kde_plasma_window_destroy(state->obj);
    delete state;
}

static const org_kde_plasma_window_listener window_listener = {
    .title_changed = window_handle_title_changed,
    .app_id_changed = window_handle_app_id_changed,
    .state_changed = window_handle_state_changed,
    .virtual_desktop_changed = nullptr,
    .themed_icon_name_changed = nullptr,
    .unmapped = window_handle_unmapped,
    .initial_state = nullptr,
    .parent_window = nullptr,
    .geometry = nullptr,
    .icon_changed = nullptr,
    .pid_changed = nullptr,
    .virtual_desktop_entered = nullptr,
    .virtual_desktop_left = nullptr,
    .application_menu = nullptr,
    .activity_entered = nullptr,
    .activity_left = nullptr,
    .resource_name_changed = nullptr,
    .client_geometry = nullptr,
};

/* ------------------------------------------------------------------ */
/* org_kde_plasma_window_management listener                           */
/* ------------------------------------------------------------------ */

static void wm_handle_show_desktop_changed(void *data, org_kde_plasma_window_management *, uint32_t state)
{
    Q_UNUSED(data);
    Q_UNUSED(state);
}

static void wm_handle_window(void *data, org_kde_plasma_window_management *, uint32_t id)
{
    Q_UNUSED(data);
    Q_UNUSED(id);
}

static void wm_handle_stacking_order_changed(void *data, org_kde_plasma_window_management *, wl_array *ids)
{
    Q_UNUSED(data);
    Q_UNUSED(ids);
}

static void wm_handle_stacking_order_uuid_changed(void *data, org_kde_plasma_window_management *, const char *uuids)
{
    Q_UNUSED(data);
    Q_UNUSED(uuids);
}

static void wm_handle_window_with_uuid(void *data, org_kde_plasma_window_management *,
                                       uint32_t id, const char *uuid)
{
    Q_UNUSED(data);
    Q_UNUSED(id);
    if (!windowManagement)
        return;
    auto *window = org_kde_plasma_window_management_get_window_by_uuid(windowManagement, uuid);
    if (!window)
        return;
    auto *state = new PlasmaWindowState;
    state->obj = window;
    org_kde_plasma_window_add_listener(window, &window_listener, state);
}

static void wm_handle_stacking_order_changed_2(void *data, org_kde_plasma_window_management *)
{
    Q_UNUSED(data);
}

static const org_kde_plasma_window_management_listener window_management_listener = {
    .show_desktop_changed = wm_handle_show_desktop_changed,
    .window = wm_handle_window,
    .stacking_order_changed = wm_handle_stacking_order_changed,
    .stacking_order_uuid_changed = wm_handle_stacking_order_uuid_changed,
    .window_with_uuid = wm_handle_window_with_uuid,
    .stacking_order_changed_2 = wm_handle_stacking_order_changed_2,
};

/* ------------------------------------------------------------------ */
/* wl_registry listener                                                */
/* ------------------------------------------------------------------ */

static void registry_handle_global(void *data, wl_registry *reg,
                                   uint32_t name, const char *interface, uint32_t version)
{
    Q_UNUSED(data);
    if (strcmp(interface, org_kde_plasma_shell_interface.name) == 0) {
        plasmaShell = static_cast<org_kde_plasma_shell *>(
            wl_registry_bind(reg, name, &org_kde_plasma_shell_interface, qMin(version, kPlasmaShellBindVersion)));
    } else if (strcmp(interface, org_kde_plasma_window_management_interface.name) == 0) {
        windowManagement = static_cast<org_kde_plasma_window_management *>(
            wl_registry_bind(reg, name, &org_kde_plasma_window_management_interface,
                             qMin(version, kWindowManagementBindVersion)));
        if (windowManagement)
            org_kde_plasma_window_management_add_listener(windowManagement, &window_management_listener, nullptr);
    } else if (strcmp(interface, wl_shell_interface.name) == 0) {
        shell = static_cast<wl_shell *>(wl_registry_bind(reg, name, &wl_shell_interface, 1));
    }
}

static void registry_handle_global_remove(void *data, wl_registry *registry, uint32_t name)
{
    Q_UNUSED(data);
    Q_UNUSED(registry);
    Q_UNUSED(name);
}

static const wl_registry_listener registry_listener = {
    .global = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};

/* ------------------------------------------------------------------ */
/* Public API                                                          */
/* ------------------------------------------------------------------ */

bool PlasmaShellManager::setAppWindowActive()
{
    if (!supportPlasmaWindowManagement())
        return false;

    org_kde_plasma_window_set_state(appWindow->obj,
                                    ORG_KDE_PLASMA_WINDOW_MANAGEMENT_STATE_ACTIVE,
                                    ORG_KDE_PLASMA_WINDOW_MANAGEMENT_STATE_ACTIVE);
    return true;
}

bool PlasmaShellManager::setAppWindowKeepAbove(bool keep)
{
    if (!supportPlasmaWindowManagement())
        return false;

    if (keep != appWindow->keepAbove) {
        org_kde_plasma_window_set_state(appWindow->obj,
                                        ORG_KDE_PLASMA_WINDOW_MANAGEMENT_STATE_KEEP_ABOVE,
                                        keep ? ORG_KDE_PLASMA_WINDOW_MANAGEMENT_STATE_KEEP_ABOVE : 0);
    }
    return true;
}

bool PlasmaShellManager::setMaximized(QWindow *window)
{
    if (!supportShell())
        return false;

    wl_surface *surface = surfaceForWindow(window);
    if (!surface)
        return false;

    wl_shell_surface *shellSurface = wl_shell_get_shell_surface(shell, surface);
    if (!shellSurface)
        return false;

    wl_shell_surface_set_maximized(shellSurface, nullptr);
    return true;
}

bool PlasmaShellManager::setRole(QWindow *window, SurfaceRole role)
{
    if (!supportPlasmaShell())
        return false;

    wl_surface *surface = surfaceForWindow(window);
    if (!surface)
        return false;

    org_kde_plasma_surface *plasmaSurface = org_kde_plasma_shell_get_surface(plasmaShell, surface);
    if (!plasmaSurface)
        return false;

    org_kde_plasma_surface_set_role(plasmaSurface, static_cast<uint32_t>(role));
    return true;
}

bool PlasmaShellManager::setPos(QWindow *window, const QPoint &pos)
{
    if (!supportPlasmaShell())
        return false;

    wl_surface *surface = surfaceForWindow(window);
    if (!surface)
        return false;

    org_kde_plasma_surface *plasmaSurface = org_kde_plasma_shell_get_surface(plasmaShell, surface);
    if (!plasmaSurface)
        return false;

    org_kde_plasma_surface_set_position(plasmaSurface, pos.x(), pos.y());
    return true;
}

bool PlasmaShellManager::supportPlasmaShell()
{
    return plasmaShell;
}

bool PlasmaShellManager::supportShell()
{
    return shell;
}

bool PlasmaShellManager::supportPlasmaWindowManagement()
{
    return windowManagement && appWindow;
}

PlasmaShellManager::PlasmaShellManager(QObject *parent) : QObject(parent)
{
    display = waylandDisplayFromApplication();
    if (!display)
        return;

    registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, this);
    wl_display_roundtrip(display); /* bind globals */
    wl_display_roundtrip(display); /* receive initial window state */
}
