cmake_minimum_required(VERSION 3.16)

set(TARGET uengine)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

add_executable(${TARGET}
    main.cpp
    commandoption.cpp
)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET} PRIVATE
    QT_DEPRECATED_WARNINGS
)

target_link_libraries(${TARGET} PRIVATE
    Qt5::Core
)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_BINDIR})