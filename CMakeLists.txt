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

set(SRC_FILES)
list(TRANSFORM SRC_FILES PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(CHAPTERS
    1.GettingStarted
)

set(1.GettingStarted
    1.HelloWindow
)

foreach (CHAPTER ${CHAPTERS})
    string(FIND ${CHAPTER} . PERIOD_POSITION)
    string(SUBSTRING ${CHAPTER} 0 ${PERIOD_POSITION} CHAPTER_NUMBER)

    foreach (SECTION ${${CHAPTER}})
        add_executable(${CHAPTER_NUMBER}.${SECTION} ${CMAKE_SOURCE_DIR}/src/${CHAPTER}/${SECTION}/main.cpp ${SRC_FILES})
    endforeach (SECTION)
endforeach (CHAPTER)
