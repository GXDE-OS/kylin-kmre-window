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

#ifndef PLASMASHELLMANAGER_H
#define PLASMASHELLMANAGER_H

#include <QObject>
#include <QWindow>

/*
 * Replacement for the discontinued KF5 KWayland client library, implemented
 * on top of libwayland-client and the org_kde_plasma_shell /
 * org_kde_plasma_window_management protocols (protocol XMLs vendored in this
 * directory).  The public API mirrors the KWayland subset that KMRE uses.
 */

class PlasmaShellManager : public QObject
{
    Q_OBJECT
public:
    static PlasmaShellManager *getInstance();

    // Mirrors the org_kde_plasma_surface role enum (previously
    // KWayland::Client::PlasmaShellSurface::Role).
    enum class SurfaceRole
    {
        Normal = 0,
        Desktop = 1,
        Panel = 2,
        OnScreenDisplay = 3,
        Notification = 4,
        ToolTip = 5,
        CriticalNotification = 6,
        AppletPopup = 7
    };

    bool setAppWindowActive(quint32 id);
    bool setAppWindowKeepAbove(quint32 id, bool keep);
    quint32 takeWindowId(QString title);
    bool setMaximized(QWindow *window);
    bool setRole(QWindow *window, SurfaceRole role);
    bool setPos(QWindow *window, const QPoint &pos);
    bool supportPlasmaShell();
    bool supportShell();
    bool supportPlasmaWindowManagement();

    // Also used by the wayland event callbacks.
    void removeUnmappedWindow(quint32 id);

signals:
    void windowAdded();
    void windowTitleChanged();

private:
    explicit PlasmaShellManager(QObject *parent = nullptr);
};

#endif // PLASMASHELLMANAGER_H
