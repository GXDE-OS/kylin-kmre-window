cmake_minimum_required(VERSION 3.16)

project(kylin-kmre-window VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

include(GNUInstallDirs)

add_subdirectory(uengine-fake)
add_subdirectory(window)
add_subdirectory(startapp)
add_subdirectory(settings-daemon)
add_subdirectory(settings-ui)
add_subdirectory(sensor)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "i386|x86_64|armhf|arm64")
    add_subdirectory(gps)
endif()