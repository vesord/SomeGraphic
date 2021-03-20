cmake_minimum_required(VERSION 3.17)
project(HelloGLUT)

set(CMAKE_C_STANDARD 99)

add_compile_options("-Wall -Wextra -Werror")

set(UTILS_SRC Utils/utils.c
              Utils/utils.h
              Utils/materials.c
              Utils/materials.h)

add_executable(TwoDimensionTransform ${UTILS_SRC} TwoDimensionTransform/main.c)
target_link_options(TwoDimensionTransform PUBLIC -framework GLUT)

add_executable(ThreeDimensionTransform ${UTILS_SRC} ThreeDimensionTransform/main.c)
target_link_options(ThreeDimensionTransform PUBLIC -framework GLUT)

add_executable(Polygons ${UTILS_SRC} Polygons/main.c)
target_link_options(Polygons PUBLIC -framework GLUT)

add_executable(SimpleFractal ${UTILS_SRC} SimpleFractal/main.c)
target_link_options(SimpleFractal PUBLIC -framework GLUT)

add_executable(Colors ${UTILS_SRC} Colors/main.c)
target_link_options(Colors PUBLIC -framework GLUT)

add_executable(LightAndMaterials ${UTILS_SRC} LightAndMaterials/main.c)
target_link_options(LightAndMaterials PUBLIC -framework GLUT)

add_executable(DeleteInvisible ${UTILS_SRC} DeleteInvisible/main.c)
target_link_options(DeleteInvisible PUBLIC -framework GLUT)

add_executable(Textures ${UTILS_SRC} Textures/main.c)
target_link_options(Textures PUBLIC -framework GLUT)