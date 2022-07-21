cmake_minimum_required(VERSION 3.22)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(GLAD ${CMAKE_SOURCE_DIR}/lib/glad/glad.c)

add_library(GLFW STATIC IMPORTED)
set_property(TARGET GLFW APPEND PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/GLFW/glfw3.lib)

link_libraries(
    GLAD
    GLFW
)
