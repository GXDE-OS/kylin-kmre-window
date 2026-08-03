cmake_minimum_required(VERSION 3.16)

set(TARGET kylin-kmre-window)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    DBus
    Network
    Concurrent
    Widgets
    Gui
    X11Extras
    Multimedia
    Xml
)

find_package(Qt5 COMPONENTS
    KWaylandClient
)

if(QT_VERSION_MINOR GREATER 14)
    find_package(Qt5 COMPONENTS
        WaylandClientPrivate
    )
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(PKGS REQUIRED
    xcb
    xcb-randr
    xcb-icccm
    xcb-xinerama
    xcb-dri2
    xcb-dri3
    gsettings-qt
    protobuf
    libdrm
    libavformat
    libavcodec
    libavutil
    libswscale
    wayland-client
)

add_executable(${TARGET}
    main.cpp

    display/displaymanager/displaymanager.cpp
    display/displaymanager/windowstretchworker.cpp

    display/displaymanager/android_display/displaywidget.cpp
    display/displaymanager/android_display/egldisplaywidget.cpp
    display/displaymanager/android_display/normaldisplaywidget.cpp

    display/displaymanager/widgets/about.cpp
    display/displaymanager/widgets/action.cpp
    display/displaymanager/widgets/autohidewidget.cpp
    display/displaymanager/widgets/crashdialog.cpp
    display/displaymanager/widgets/dialog.cpp
    display/displaymanager/widgets/loadingwidget.cpp
    display/displaymanager/widgets/lockwidget.cpp
    display/displaymanager/widgets/menu.cpp
    display/displaymanager/widgets/messagebox.cpp
    display/displaymanager/widgets/popuptip.cpp
    display/displaymanager/widgets/recordscreenwidget.cpp
    display/displaymanager/widgets/scrollsettingwidget.cpp
    display/displaymanager/widgets/systembutton.cpp
    display/displaymanager/widgets/titlebar.cpp
    display/displaymanager/widgets/titlebarjoystick.cpp
    display/displaymanager/widgets/warningnotice.cpp
    display/displaymanager/widgets/xatom-helper.cpp

    display/displaybackend/displaybackend.cpp
    display/displaybackend/display_control.cpp
    display/displaybackend/displayconnection.cpp
    display/displaybackend/kmredisplay.cpp

    display/displayfrontend/displayhelper.cpp
    display/displayfrontend/displayworkmanager.cpp

    display/displayfrontend/egl/egl_display_helper.cpp
    display/displayfrontend/egl/egl_display_utils.cpp
    display/displayfrontend/egl/egl_display_work_manager.cpp

    display/displayfrontend/emugl/emugl_display_helper.cpp
    display/displayfrontend/emugl/emugl_display_utils.cpp
    display/displayfrontend/emugl/emugl_display_work_manager.cpp

    display/displayfrontend/gles/gles_display_helper.cpp
    display/displayfrontend/gles/gles_display_utils.cpp
    display/displayfrontend/gles/gles_display_work_manager.cpp
    display/displayfrontend/gles/texture.cpp

    display/drm/authenticate_magic.c

    common/common.h
    common/libwrapper.h
    common/shader.cpp
    common/singleton.h
    common/socket_helper.cpp
    common/utils.cpp

    communication/app_control_manager.cpp
    communication/backendworker.cpp

    communication/cmdprocessor/kmre_message_parser.cpp
    communication/cmdprocessor/kmre_message_receiver.cpp

    communication/connection/kmre_connection_worker.cpp
    communication/connection/kmre_service_loop.cpp
    communication/connection/kmre_socket_connector.cpp
    communication/connection/kmre_socket_manager.cpp

    communication/network/networkconfig.cpp
    communication/network/networksettings.cpp

    communication/protobuf/KmreCore.pb.cc

    config/appsettings.cpp
    config/kmreenv.cpp
    config/preferences.cpp
    config/sessionsettings.cpp

    dbus/dbusclient.cpp
    dbus/screencapturedbus.cpp
    dbus/window_dbus.cpp

    window/kmreapplication.cpp
    window/kmrewindow.cpp
    window/windowmanager.cpp

    wayland/gtk/GtkShell1.cpp
    wayland/gtk/GtkShellManager.cpp
    wayland/gtk/qwayland-gtk-shell.cpp

    wayland/ukui/plasma-shell-manager.cpp
    wayland/ukui/ukui-decoration-manager.cpp

    wayland/xdg/XdgActivationV1.cpp
    wayland/xdg/XdgManager.cpp
    wayland/xdg/wayland-xdg-activation-v1-protocol.cpp
    wayland/xdg/qwayland-xdg-activation-v1.cpp

    utilitys/clipboard.cpp
    utilitys/notification.cpp
    utilitys/screencapture.cpp
    utilitys/tray.cpp

    gamekey/accelatekey.cpp
    gamekey/basekey.cpp
    gamekey/directtypebasekey.cpp
    gamekey/gamekeymanager.cpp
    gamekey/gamekeystackwidget.cpp
    gamekey/gamekeytimer.cpp
    gamekey/joystickautokey.cpp
    gamekey/joystickbasekey.cpp
    gamekey/joystickcombokey.cpp
    gamekey/joystickdirectkey.cpp
    gamekey/joystickgamekeymanager.cpp
    gamekey/joystickleftrock.cpp
    gamekey/joystickmanager.cpp
    gamekey/joystickrightrock.cpp
    gamekey/joystickrockbasekey.cpp
    gamekey/joysticksinglebasekey.cpp
    gamekey/joysticksinglekey.cpp
    gamekey/joysticksetwidget.cpp
    gamekey/keymousesetwidget.cpp
    gamekey/keyboardgamekeymanager.cpp
    gamekey/ktabbar.cpp
    gamekey/mousebasekey.cpp
    gamekey/mousecrosshairkey.cpp
    gamekey/mousefirekey.cpp
    gamekey/mouseviewkey.cpp
    gamekey/nojoystickwidget.cpp
    gamekey/qjoysticks.cpp
    gamekey/sdl_joysticks.cpp
    gamekey/sensitivitywidget.cpp
    gamekey/settingspanel.cpp
    gamekey/shademask.cpp
    gamekey/shadewidget.cpp
    gamekey/steelingwheel.cpp
    gamekey/singlekey.cpp
    gamekey/themeController.cpp
    gamekey/tipWidget.cpp
    gamekey/toast.cpp

    event/eventmanager.cpp

    event/inputmethod/inputmethodchannel.cpp

    event/keyboard/keyevent_handler.cpp
    event/keyboard/keyevent_worker.cpp
    event/keyboard/kmre_keycode.c

    event/mousekey/common/fd.cpp
    event/mousekey/common/null_message_processor.cpp
    event/mousekey/input/device.cpp
    event/mousekey/input/manager.cpp
    event/mousekey/kmreplatform.cpp
    event/mousekey/network/base_socket_messenger.cpp
    event/mousekey/network/local_socket_messenger.cpp
    event/mousekey/network/published_socket_connector.cpp
    event/mousekey/network/socket_connection.cpp
    event/mousekey/runtime.cpp

    screensharing/grabber.cpp
    screensharing/grabber_x11.cpp
    screensharing/grabberhelper.cpp
    screensharing/maskwindow.cpp
    screensharing/screensharing.cpp
    screensharing/sharingselectwindow.cpp

    record/AV/AVWrapper.cpp
    record/AV/FastResampler.cpp
    record/AV/FastResampler_FirFilter_Fallback.cpp
    record/AV/FastScaler.cpp
    record/AV/FastScaler_Convert_Fallback.cpp
    record/AV/FastScaler_Scale_Fallback.cpp
    record/AV/FastScaler_Scale_Generic.cpp
    record/AV/SourceSink.cpp

    record/AV/Input/ALSAInput.cpp
    record/AV/Input/VideoBaseInput.cpp
    record/AV/Input/X11Input.cpp

    record/AV/Output/AudioEncoder.cpp
    record/AV/Output/BaseEncoder.cpp
    record/AV/Output/Muxer.cpp
    record/AV/Output/OutputManager.cpp
    record/AV/Output/Synchronizer.cpp
    record/AV/Output/VideoEncoder.cpp

    etc/resources/qjoysticks-res.qrc
)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/dbus
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/communication
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/window
    ${CMAKE_CURRENT_SOURCE_DIR}/gamekey
    ${CMAKE_CURRENT_SOURCE_DIR}/utilitys
    ${CMAKE_CURRENT_SOURCE_DIR}/display
    ${CMAKE_CURRENT_SOURCE_DIR}/display/displaybackend
    ${CMAKE_CURRENT_SOURCE_DIR}/display/displayfrontend
    ${CMAKE_CURRENT_SOURCE_DIR}/display/displaymanager
    ${CMAKE_CURRENT_SOURCE_DIR}/event
    ${CMAKE_CURRENT_SOURCE_DIR}/record
    ${CMAKE_CURRENT_SOURCE_DIR}/screensharing
    ${CMAKE_CURRENT_SOURCE_DIR}/wayland/ukui
    ${CMAKE_CURRENT_SOURCE_DIR}/wayland/drm
    ${CMAKE_CURRENT_SOURCE_DIR}/wayland/xdg
    ${CMAKE_CURRENT_SOURCE_DIR}/wayland/gtk
    /usr/include/DisplayControl
    /usr/include/boost
)

target_compile_definitions(${TARGET} PRIVATE
    QT_DEPRECATED_WARNINGS
    SDL_SUPPORTED
    KYLIN_V10
)

target_link_libraries(${TARGET} PRIVATE
    Qt5::Core
    Qt5::DBus
    Qt5::Network
    Qt5::Concurrent
    Qt5::Widgets
    Qt5::Gui
    Qt5::X11Extras
    Qt5::Multimedia
    Qt5::Xml
)

if(Qt5KWaylandClient_FOUND)
    target_link_libraries(${TARGET} PRIVATE
        Qt5::KWaylandClient
    )
endif()

if(QT_VERSION_MINOR GREATER 14 AND Qt5WaylandClientPrivate_FOUND)
    target_link_libraries(${TARGET} PRIVATE
        Qt5::WaylandClientPrivate
    )
endif()

target_link_libraries(${TARGET} PRIVATE
    ${PKGS_LIBRARIES}
    ${CMAKE_DL_LIBS}
    X11
    Xtst
    pthread
    boost_system
    boost_filesystem
    DisplayControl
    GLESv2
    EGL
    asound
    SDL2
    wayland-client
    epoxy
    systemd
    Xfixes
    Xinerama
    Xext
)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    ../data/games.json
    ../data/warning.json
    ../data/feature_config.ini
    DESTINATION ${CMAKE_INSTALL_DATADIR}/kmre
)

install(FILES
    ../data/cn.kylinos.Kmre.Window.service
    DESTINATION ${CMAKE_INSTALL_DATADIR}/dbus-1/services
)

install(FILES
    ../data/kmre_data_app_list.xml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/kmre/config
)

execute_process(
    COMMAND bash -c "cat /etc/lsb-release | grep -ci -e 'Kylin\\ V10\\ Professional' -e 'Kylin\\ V10\\ SP1' -e 'Kylin\\ V10\\ SP2' -e 'openKylin' -e 'Ubuntu'"
    OUTPUT_VARIABLE V10_PRO
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(V10_PRO EQUAL 0)
    install(DIRECTORY ../data/v10/kmre/ DESTINATION ${CMAKE_INSTALL_DATADIR}/kylin-user-guide/data/guide/kmre)
else()
    install(DIRECTORY ../data/v10pro/kmre/ DESTINATION ${CMAKE_INSTALL_DATADIR}/kylin-user-guide/data/guide/kmre)
endif()

add_custom_command(
    TARGET ${TARGET}
    PRE_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/gen_proto_and_qdbus_src.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating protobuf and qdbus sources..."
)

add_custom_command(
    TARGET ${TARGET}
    PRE_BUILD
    COMMAND wayland-scanner client-header ${CMAKE_CURRENT_SOURCE_DIR}/wayland/remote-access.xml ${CMAKE_CURRENT_SOURCE_DIR}/wayland/remote-access.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating wayland remote-access header..."
)

add_custom_command(
    TARGET ${TARGET}
    PRE_BUILD
    COMMAND wayland-scanner private-code ${CMAKE_CURRENT_SOURCE_DIR}/wayland/remote-access.xml ${CMAKE_CURRENT_SOURCE_DIR}/wayland/remote-access.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating wayland remote-access code..."
)

add_custom_command(
    TARGET ${TARGET}
    PRE_BUILD
    COMMAND wayland-scanner client-header ${CMAKE_CURRENT_SOURCE_DIR}/wayland/xdg-output-unstable-v1.xml ${CMAKE_CURRENT_SOURCE_DIR}/wayland/xdg-output-unstable-v1.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating wayland xdg-output header..."
)

add_custom_command(
    TARGET ${TARGET}
    PRE_BUILD
    COMMAND wayland-scanner private-code ${CMAKE_CURRENT_SOURCE_DIR}/wayland/xdg-output-unstable-v1.xml ${CMAKE_CURRENT_SOURCE_DIR}/wayland/xdg-output-unstable-v1.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating wayland xdg-output code..."
)