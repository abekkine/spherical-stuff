cmake_minimum_required(VERSION 3.15)

project(spherical)

include_directories(/usr/include/glm)

add_executable(gfxTest gfxTest.cpp)
target_link_libraries(gfxTest
    GL
    glfw
)
