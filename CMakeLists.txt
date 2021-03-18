cmake_minimum_required(VERSION 3.17)
project(HelloOpenGL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wconversion -O2 -Wno-unused -Wno-unused-variable -Wno-unused-parameter")
set(CMAKE_EXE_LINKER_FLAGS "-L.. -framework OpenGL -framework Cocoa -framework IOKit")

include_directories(glew/include)
include_directories(glfw/include)
include_directories(Utils)
include_directories(Shaders)
include_directories(.)

add_subdirectory(glfw)

set(UTILS_SRC Utils/utils.c
              Utils/utils.h)

set(OPENGL_LIBS libglfw3.a libGLEW.a)

add_executable(HelloWindow HelloWindow/main.cpp)
target_link_libraries(HelloWindow ${OPENGL_LIBS})

add_executable(HelloTriangle ${UTILS_SRC} HelloTriangle/main.c)
target_link_libraries(HelloTriangle ${OPENGL_LIBS})

add_executable(TwoDimensionTransform ${UTILS_SRC} TwoDimensionTransform/main.c)
target_link_options(TwoDimensionTransform PUBLIC -framework GLUT)

add_executable(ThreeDimensionTransform ${UTILS_SRC} ThreeDimensionTransform/main.c)
target_link_options(ThreeDimensionTransform PUBLIC -framework GLUT)

add_executable(Polygons ${UTILS_SRC} Polygons/main.c)
target_link_options(Polygons PUBLIC -framework GLUT)
