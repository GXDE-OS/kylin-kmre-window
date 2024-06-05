// This file was generated by qtwaylandscanner
// source file is ./xdg-activation-v1.xml

#ifndef QT_WAYLAND_XDG_ACTIVATION_V1
#define QT_WAYLAND_XDG_ACTIVATION_V1

#include "wayland-xdg-activation-v1-client-protocol.h"
#include <QByteArray>
#include <QString>

#if QT_VERSION < QT_VERSION_CHECK(6, 3, 0)

struct wl_registry;

QT_BEGIN_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wmissing-field-initializers")

namespace QtWayland {
    class  xdg_activation_v1
    {
    public:
        xdg_activation_v1(struct ::wl_registry *registry, int id, int version);
        xdg_activation_v1(struct ::xdg_activation_v1 *object);
        xdg_activation_v1();

        virtual ~xdg_activation_v1();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::xdg_activation_v1 *object);

        struct ::xdg_activation_v1 *object() { return m_xdg_activation_v1; }
        const struct ::xdg_activation_v1 *object() const { return m_xdg_activation_v1; }
        static xdg_activation_v1 *fromObject(struct ::xdg_activation_v1 *object);

        bool isInitialized() const;

        static const struct ::wl_interface *interface();

        void destroy();
        struct ::xdg_activation_token_v1 *get_activation_token();
        void activate(const QString &token, struct ::wl_surface *surface);

    private:
        struct ::xdg_activation_v1 *m_xdg_activation_v1;
    };

    class  xdg_activation_token_v1
    {
    public:
        xdg_activation_token_v1(struct ::wl_registry *registry, int id, int version);
        xdg_activation_token_v1(struct ::xdg_activation_token_v1 *object);
        xdg_activation_token_v1();

        virtual ~xdg_activation_token_v1();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::xdg_activation_token_v1 *object);

        struct ::xdg_activation_token_v1 *object() { return m_xdg_activation_token_v1; }
        const struct ::xdg_activation_token_v1 *object() const { return m_xdg_activation_token_v1; }
        static xdg_activation_token_v1 *fromObject(struct ::xdg_activation_token_v1 *object);

        bool isInitialized() const;

        static const struct ::wl_interface *interface();

        enum error {
            error_already_used = 0, // The token has already been used previously
        };

        void set_serial(uint32_t serial, struct ::wl_seat *seat);
        void set_app_id(const QString &app_id);
        void set_surface(struct ::wl_surface *surface);
        void commit();
        void destroy();

    protected:
        virtual void xdg_activation_token_v1_done(const QString &token);

    private:
        void init_listener();
        static const struct xdg_activation_token_v1_listener m_xdg_activation_token_v1_listener;
        static void handle_done(
            void *data,
            struct ::xdg_activation_token_v1 *object,
            const char *token);
        struct ::xdg_activation_token_v1 *m_xdg_activation_token_v1;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif

#endif