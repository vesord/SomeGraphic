cmake_minimum_required(VERSION 3.17)
project(HelloOpenGL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wconversion -O2 -Wno-unused -Wno-unused-variable -Wno-unused-parameter")
set(CMAKE_EXE_LINKER_FLAGS "-L.. -framework OpenGL -framework Cocoa -framework IOKit")
#-framework OpenGL
include_directories(GL)
include_directories(GLFW)
include_directories(.)

add_executable(HelloOpenGL main.cpp)
target_link_libraries(HelloOpenGL libglfw3.a)
target_link_libraries(HelloOpenGL libGLEW.a)
