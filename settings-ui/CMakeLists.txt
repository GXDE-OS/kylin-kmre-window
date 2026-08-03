cmake_minimum_required(VERSION 3.16)

set(TARGET kylin-kmre-settings)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    DBus
    Concurrent
    Multimedia
    Xml
    Widgets
    Gui
    X11Extras
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PKGS REQUIRED
    gsettings-qt
)

add_executable(${TARGET}
    main.cpp
    dbusclient.cpp
    developerwidget.cpp
    gamelistview.cpp
    generalsettingwidget.cpp
    global.cpp
    phoneinfowidget.cpp
    popuptip.cpp
    settingsframe.cpp
    settingscrollcontent.cpp
    displaymodewidget.cpp
    dockeripwidget.cpp
    glesversionwidget.cpp
    gamewidget.cpp
    settingsitem.cpp
    settingsgroup.cpp
    inputitem.cpp
    ipitem.cpp
    messagebox.cpp
    netmaskitem.cpp
    navgationbutton.cpp
    addgamewidget.cpp
    removegamewidget.cpp
    gamelistitem.cpp
    radiobuttonitem.cpp
    camerawidget.cpp
    cleanerwidget.cpp
    cleaneritem.cpp
    logwidget.cpp
    appmultiplierwidget.cpp
    switchbutton.cpp
    switchwidget.cpp
    preferences.cpp
    utils.cpp
    xatom-helper.cpp
    appwidget.cpp
    appview.cpp
    appitem.cpp
    appsettingspanel.cpp
    advancedwidget.cpp
    appconfiguration.cpp

    qtsingleapplication/qtsingleapplication.cpp
    qtsingleapplication/qtlocalpeer.cpp

    res.qrc
)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication
)

target_compile_definitions(${TARGET} PRIVATE
    QT_DEPRECATED_WARNINGS
    SINGLE_INSTANCE
)

target_link_libraries(${TARGET} PRIVATE
    Qt5::Core
    Qt5::DBus
    Qt5::Concurrent
    Qt5::Multimedia
    Qt5::Xml
    Qt5::Widgets
    Qt5::Gui
    Qt5::X11Extras
    ${PKGS_LIBRARIES}
    ${CMAKE_DL_LIBS}
    X11
)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    ../data/rm_kmre.sh
    DESTINATION ${CMAKE_INSTALL_DATADIR}/kmre
)