cmake_minimum_required(VERSION 3.16)

set(TARGET kylin-kmre-sensorwindow)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    DBus
    Network
    Widgets
)

add_executable(${TARGET}
    main.cpp
    directbtn.cpp
    sensorwindow.cpp

    qtsingleapplication/qtsingleapplication.cpp
    qtsingleapplication/qtlocalpeer.cpp
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
    ${CMAKE_DL_LIBS}
    X11
)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_BINDIR})