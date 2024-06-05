// This file was generated by qtwaylandscanner
// source file is ./xdg-activation-v1.xml

#include <wayland-client-protocol.h>

#include "qwayland-xdg-activation-v1.h"

#if QT_VERSION < QT_VERSION_CHECK(6, 3, 0)

QT_BEGIN_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wmissing-field-initializers")

namespace QtWayland {

#if (WAYLAND_VERSION_MAJOR == 1 && WAYLAND_VERSION_MINOR >= 20) || WAYLAND_VERSION_MAJOR > 1
static inline void *wlRegistryBind(struct ::wl_registry *registry, uint32_t name, const struct ::wl_interface *interface, uint32_t version)
{
    const uint32_t bindOpCode = 0;
#if (WAYLAND_VERSION_MAJOR == 1 && WAYLAND_VERSION_MINOR > 10) || WAYLAND_VERSION_MAJOR > 1
    return (void *) wl_proxy_marshal_constructor_versioned((struct wl_proxy *) registry,
        bindOpCode, interface, version, name, interface->name, version, nullptr);
#else
    return (void *) wl_proxy_marshal_constructor((struct wl_proxy *) registry,
        bindOpCode, interface, name, interface->name, version, nullptr);
#endif
}
#endif

    xdg_activation_v1::xdg_activation_v1(struct ::wl_registry *registry, int id, int version)
    {
        init(registry, id, version);
    }

    xdg_activation_v1::xdg_activation_v1(struct ::xdg_activation_v1 *obj)
        : m_xdg_activation_v1(obj)
    {
    }

    xdg_activation_v1::xdg_activation_v1()
        : m_xdg_activation_v1(nullptr)
    {
    }

    xdg_activation_v1::~xdg_activation_v1()
    {
    }

    void xdg_activation_v1::init(struct ::wl_registry *registry, int id, int version)
    {
#if (WAYLAND_VERSION_MAJOR == 1 && WAYLAND_VERSION_MINOR >= 20) || WAYLAND_VERSION_MAJOR > 1
        m_xdg_activation_v1 = static_cast<struct ::xdg_activation_v1 *>(wlRegistryBind(registry, id, &xdg_activation_v1_interface, version));
#else
        m_xdg_activation_v1 = static_cast<struct ::xdg_activation_v1 *>(::wl_registry_bind(registry, id, &xdg_activation_v1_interface, version));
#endif
    }

    void xdg_activation_v1::init(struct ::xdg_activation_v1 *obj)
    {
        m_xdg_activation_v1 = obj;
    }

    xdg_activation_v1 *xdg_activation_v1::fromObject(struct ::xdg_activation_v1 *object)
    {
        return static_cast<xdg_activation_v1 *>(xdg_activation_v1_get_user_data(object));
    }

    bool xdg_activation_v1::isInitialized() const
    {
        return m_xdg_activation_v1 != nullptr;
    }

    const struct wl_interface *xdg_activation_v1::interface()
    {
        return &::xdg_activation_v1_interface;
    }

    void xdg_activation_v1::destroy()
    {
        ::xdg_activation_v1_destroy(
            m_xdg_activation_v1);
        m_xdg_activation_v1 = nullptr;
    }

    struct ::xdg_activation_token_v1 *xdg_activation_v1::get_activation_token()
    {
        return ::xdg_activation_v1_get_activation_token(
            m_xdg_activation_v1);
    }

    void xdg_activation_v1::activate(const QString &token, struct ::wl_surface *surface)
    {
        ::xdg_activation_v1_activate(
            m_xdg_activation_v1,
            token.toUtf8().constData(),
            surface);
    }

    xdg_activation_token_v1::xdg_activation_token_v1(struct ::wl_registry *registry, int id, int version)
    {
        init(registry, id, version);
    }

    xdg_activation_token_v1::xdg_activation_token_v1(struct ::xdg_activation_token_v1 *obj)
        : m_xdg_activation_token_v1(obj)
    {
        init_listener();
    }

    xdg_activation_token_v1::xdg_activation_token_v1()
        : m_xdg_activation_token_v1(nullptr)
    {
    }

    xdg_activation_token_v1::~xdg_activation_token_v1()
    {
    }

    void xdg_activation_token_v1::init(struct ::wl_registry *registry, int id, int version)
    {
#if (WAYLAND_VERSION_MAJOR == 1 && WAYLAND_VERSION_MINOR >= 20) || WAYLAND_VERSION_MAJOR > 1
        m_xdg_activation_token_v1 = static_cast<struct ::xdg_activation_token_v1 *>(wlRegistryBind(registry, id, &xdg_activation_token_v1_interface, version));
#else
        m_xdg_activation_token_v1 = static_cast<struct ::xdg_activation_token_v1 *>(::wl_registry_bind(registry, id, &xdg_activation_token_v1_interface, version));
#endif
        init_listener();
    }

    void xdg_activation_token_v1::init(struct ::xdg_activation_token_v1 *obj)
    {
        m_xdg_activation_token_v1 = obj;
        init_listener();
    }

    xdg_activation_token_v1 *xdg_activation_token_v1::fromObject(struct ::xdg_activation_token_v1 *object)
    {
        if (wl_proxy_get_listener((struct ::wl_proxy *)object) != (void *)&m_xdg_activation_token_v1_listener)
            return nullptr;
        return static_cast<xdg_activation_token_v1 *>(xdg_activation_token_v1_get_user_data(object));
    }

    bool xdg_activation_token_v1::isInitialized() const
    {
        return m_xdg_activation_token_v1 != nullptr;
    }

    const struct wl_interface *xdg_activation_token_v1::interface()
    {
        return &::xdg_activation_token_v1_interface;
    }

    void xdg_activation_token_v1::set_serial(uint32_t serial, struct ::wl_seat *seat)
    {
        ::xdg_activation_token_v1_set_serial(
            m_xdg_activation_token_v1,
            serial,
            seat);
    }

    void xdg_activation_token_v1::set_app_id(const QString &app_id)
    {
        ::xdg_activation_token_v1_set_app_id(
            m_xdg_activation_token_v1,
            app_id.toUtf8().constData());
    }

    void xdg_activation_token_v1::set_surface(struct ::wl_surface *surface)
    {
        ::xdg_activation_token_v1_set_surface(
            m_xdg_activation_token_v1,
            surface);
    }

    void xdg_activation_token_v1::commit()
    {
        ::xdg_activation_token_v1_commit(
            m_xdg_activation_token_v1);
    }

    void xdg_activation_token_v1::destroy()
    {
        ::xdg_activation_token_v1_destroy(
            m_xdg_activation_token_v1);
        m_xdg_activation_token_v1 = nullptr;
    }

    void xdg_activation_token_v1::xdg_activation_token_v1_done(const QString &)
    {
    }

    void xdg_activation_token_v1::handle_done(
        void *data,
        struct ::xdg_activation_token_v1 *object,
        const char *token)
    {
        Q_UNUSED(object);
        static_cast<xdg_activation_token_v1 *>(data)->xdg_activation_token_v1_done(
            QString::fromUtf8(token));
    }

    const struct xdg_activation_token_v1_listener xdg_activation_token_v1::m_xdg_activation_token_v1_listener = {
        xdg_activation_token_v1::handle_done,
    };

    void xdg_activation_token_v1::init_listener()
    {
        xdg_activation_token_v1_add_listener(m_xdg_activation_token_v1, &m_xdg_activation_token_v1_listener, this);
    }
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
