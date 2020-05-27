cmake_minimum_required(VERSION 3.7)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

if (UNIX)

    # set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=* -extra-arg=-std=${CMAKE_CXX_STANDARD}")
    add_compile_options(-Wall -Wextra -Wpedantic -O3)

    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    find_package (Threads)
    include_directories(${OPENGL_INCLUDE_DIRS} ${X11_INCLUDE_DIRS})

    set(GFX_FILES
        ../src/source/glfunctions.cpp
        ../src/source/linux/renderer.cpp
        ../src/source/linux/input/keyboard.cpp
        ../src/source/linux/input/mouse.cpp
        ../src/source/draws/circle.cpp
        ../src/source/draws/rectangle.cpp
        ../src/source/draws/shape.cpp
        ../src/source/draws/sprite.cpp
        ../src/source/draws/transformation.cpp
        ../src/source/utils/color.cpp
        ../src/source/utils/utils.cpp
    )

    add_executable(straight_line straight_line.cpp ${GFX_FILES})
    target_link_libraries(straight_line ${OPENGL_LIBRARIES} ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    add_executable(multiple_windows multiple_windows.cpp ${GFX_FILES})
    target_link_libraries(multiple_windows ${OPENGL_LIBRARIES} ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    add_executable(loading_image loading_image.cpp ${GFX_FILES})
    target_link_libraries(loading_image ${OPENGL_LIBRARIES} ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    endif()