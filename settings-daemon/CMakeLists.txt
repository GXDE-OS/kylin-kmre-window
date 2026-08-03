cmake_minimum_required(VERSION 3.16)

set(TARGET kylin-kmre-settings-daemon)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Network
    DBus
    Xml
)

add_executable(${TARGET}
    main.cpp
    prefmanager.cpp
)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET} PRIVATE
    QT_DEPRECATED_WARNINGS
)

target_link_libraries(${TARGET} PRIVATE
    Qt5::Core
    Qt5::Network
    Qt5::DBus
    Qt5::Xml
)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    cn.kylinos.Kmre.Pref.service
    DESTINATION ${CMAKE_INSTALL_DATADIR}/dbus-1/system-services
)

install(FILES
    cn.kylinos.Kmre.Pref.conf
    DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/dbus-1/system.d
)