cmake_minimum_required(VERSION 3.7)

project (GFX)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/)
set(CMAKE_BUILD_TYPE Release)

if (UNIX)

    include_directories(
        ../src/external_libs
        ../src/includes/
        ../src/includes/linux
        ../src/includes/linux/input
        ../src/includes/draws
        ../src/includes/util
    )

    add_library(${CMAKE_PROJECT_NAME} STATIC
        ../src/source/glfunctions.cpp
        ../src/source/linux/renderer.cpp
        ../src/source/linux/input/keyboard.cpp
        ../src/source/linux/input/mouse.cpp
        ../src/source/draws/circle.cpp
        ../src/source/draws/rectangle.cpp
        ../src/source/draws/shape.cpp
        ../src/source/draws/sprite.cpp
        ../src/source/draws/transformation.cpp
    )

endif()