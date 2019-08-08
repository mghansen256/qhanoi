cmake_minimum_required(VERSION 3.1.0)

project(qhanoi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# This statement does not work with the Android build yet,
# but with the Ubuntu build.
# Probably need to set CMAKE_PREFIX or similar variable for
# this to work.
#find_package(Qt5 COMPONENTS Widgets Xml Svg REQUIRED)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Svg REQUIRED)

add_subdirectory(src)


