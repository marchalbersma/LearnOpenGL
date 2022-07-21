cmake_minimum_required(VERSION 3.22)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    string(APPEND CMAKE_EXE_LINKER_FLAGS " /NODEFAULTLIB:msvcrt.lib")
endif (MSVC)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(GLAD ${CMAKE_SOURCE_DIR}/lib/glad/glad.c)

add_library(GLFW STATIC IMPORTED)
set_property(TARGET GLFW APPEND PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/GLFW/glfw3.lib)

link_libraries(
    GLAD
    GLFW
)

set(SRC_FILES
    Glad.cpp
    GLFW.cpp
    Shader.cpp
)
list(TRANSFORM SRC_FILES PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(CHAPTERS
    1.GettingStarted
)

set(1.GettingStarted
    1.HelloWindow
    2.HelloTriangle
)

foreach (CHAPTER ${CHAPTERS})
    string(FIND ${CHAPTER} . PERIOD_POSITION)
    string(SUBSTRING ${CHAPTER} 0 ${PERIOD_POSITION} CHAPTER_NUMBER)

    foreach (SECTION ${${CHAPTER}})
        set(SECTION_NAME ${CHAPTER_NUMBER}.${SECTION})
        set(SECTION_DIR ${CMAKE_SOURCE_DIR}/src/${CHAPTER}/${SECTION})

        add_executable(${SECTION_NAME} ${SECTION_DIR}/main.cpp ${SRC_FILES})

        file(GLOB SHADERS
            ${SECTION_DIR}/*.frag
            ${SECTION_DIR}/*.vert
        )

        foreach (SHADER ${SHADERS})
            add_custom_command(
                TARGET ${SECTION_NAME}
                PRE_BUILD COMMAND ${CMAKE_COMMAND}
                -E copy_if_different ${SHADER} $<TARGET_FILE_DIR:${SECTION_NAME}>
            )
        endforeach (SHADER)
    endforeach (SECTION)
endforeach (CHAPTER)
