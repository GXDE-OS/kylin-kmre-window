cmake_minimum_required(VERSION 3.16)

set(TARGET kylin-kmre-gps)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    DBus
    Network
    Widgets
    WebEngineWidgets
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PKGS REQUIRED
    gsettings-qt
)

add_executable(${TARGET}
    main.cpp
    currentlocationview.cpp
    currentlocation.cpp
    formatconversion.cpp
    gpswindow.cpp
    locationget.cpp
    locationlistitem.cpp
    locationlistwidget.cpp
    searchbox.cpp
    searchview.cpp
    dbusclient.cpp

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
    Qt5::Gui
    Qt5::DBus
    Qt5::Network
    Qt5::Widgets
    Qt5::WebEngineWidgets
    ${PKGS_LIBRARIES}
)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    data/org.kylin.gps.gschema.xml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/glib-2.0/schemas
)

install(FILES
    data/gps.conf
    DESTINATION ${CMAKE_INSTALL_DATADIR}/kmre
)