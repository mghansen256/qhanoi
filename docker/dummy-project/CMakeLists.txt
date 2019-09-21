cmake_minimum_required(VERSION 3.1.0)

project(dummy-project LANGUAGES CXX)
set(CMAKE_VERBOSE_MAKEFILE ON)

if(NOT ANDROID)
    MESSAGE(FATAL_ERROR "This project can only be built for Android.")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# we need to find some package in order to find Qt at all
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Svg REQUIRED)
include_directories(${QT_QTSVG_INCLUDE_DIR})

set(dummy_project_src
        main.cpp
   )

add_library(dummy_project SHARED ${dummy_project_src})
target_link_libraries(dummy_project Qt5::Widgets Qt5::Xml Qt5::Svg ${QT_LIBRARIES} ${QT_QTSVG_LIBRARY})
include(../../cmake/qt-android-cmake/AddQtAndroidApk.cmake)
add_qt_android_apk(dummy_project.apk dummy_project)
