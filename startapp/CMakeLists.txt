cmake_minimum_required(VERSION 3.16)

set(TARGET startapp)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    DBus
    Xml
    Widgets
    X11Extras
)

add_executable(${TARGET}
    main.cpp
    dialog.cpp
    dbus_client.cpp
    preferences.cpp
    start_control.cpp
    utils.cpp
    worker.cpp
    get_userinfo.cpp
    containerthread.cpp
    preinstallappmanager.cpp

    dialog.ui
    qsrc.qrc
)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET} PRIVATE
    QT_DEPRECATED_WARNINGS
    KYLIN_V10
)

target_link_libraries(${TARGET} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::DBus
    Qt5::Xml
    Qt5::Widgets
    Qt5::X11Extras
    ${CMAKE_DL_LIBS}
    X11
    pciaccess
)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    startapp.desktop
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/xdg/autostart
)

install(FILES
    kmre-com.android.settings.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)

install(FILES
    images/kylin-kmre.png
    DESTINATION ${CMAKE_INSTALL_DATADIR}/pixmaps
)

install(FILES
    ../data/app.json
    DESTINATION ${CMAKE_INSTALL_DATADIR}/kmre
)