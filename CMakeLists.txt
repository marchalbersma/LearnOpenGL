cmake_minimum_required(VERSION 3.22)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    string(APPEND CMAKE_EXE_LINKER_FLAGS " /NODEFAULTLIB:msvcrt.lib")
endif (MSVC)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(ASSIMP STATIC IMPORTED)
set_property(TARGET ASSIMP APPEND PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/assimp/assimp-vc143-mt.lib)

add_library(GLAD ${CMAKE_SOURCE_DIR}/lib/glad/glad.c)

add_library(GLFW STATIC IMPORTED)
set_property(TARGET GLFW APPEND PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/GLFW/glfw3.lib)

link_libraries(
    ASSIMP
    GLAD
    GLFW
)

set(SRC_FILES
    Camera.cpp
    FileSystem.cpp
    Glad.cpp
    GLFW.cpp
    Mesh.cpp
    Model.cpp
    Shader.cpp
    Texture.cpp
    Vertex.cpp
)
list(TRANSFORM SRC_FILES PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(CHAPTERS
    1.GettingStarted
    2.Lighting
    3.ModelLoading
)

set(1.GettingStarted
    1.HelloWindow
    2.HelloTriangle
    3.Shaders
    4.Textures
    5.Transformations
    6.CoordinateSystems
    7.Camera
)

set(2.Lighting
    1.Colors
    2.BasicLighting
    3.Materials
    4.LightingMaps
    5.LightCasters
    6.MultipleLights
)

set(3.ModelLoading
    1.Model
)

file(GLOB DLLS ${CMAKE_SOURCE_DIR}/dll/*.dll)
file(GLOB_RECURSE RESOURCES ${CMAKE_SOURCE_DIR}/resources/*.*)

foreach (CHAPTER ${CHAPTERS})
    string(FIND ${CHAPTER} . PERIOD_POSITION)
    string(SUBSTRING ${CHAPTER} 0 ${PERIOD_POSITION} CHAPTER_NUMBER)

    foreach (SECTION ${${CHAPTER}})
        set(SECTION_NAME ${CHAPTER_NUMBER}.${SECTION})
        set(SECTION_DIR ${CMAKE_SOURCE_DIR}/src/${CHAPTER}/${SECTION})

        add_executable(${SECTION_NAME} ${SECTION_DIR}/main.cpp ${SRC_FILES})

        file(GLOB SHADERS
            ${SECTION_DIR}/shaders/*.frag
            ${SECTION_DIR}/shaders/*.vert
        )

        foreach (SHADER ${SHADERS})
            get_filename_component(SHADER_FILENAME ${SHADER} NAME)

            add_custom_command(
                TARGET ${SECTION_NAME}
                PRE_BUILD COMMAND ${CMAKE_COMMAND}
                -E copy_if_different ${SHADER} $<TARGET_FILE_DIR:${SECTION_NAME}>/shaders/${SHADER_FILENAME}
            )
        endforeach (SHADER)

        foreach (DLL ${DLLS})
            get_filename_component(DLL_FILENAME ${DLL} NAME)

            add_custom_command(
                TARGET ${SECTION_NAME}
                PRE_BUILD COMMAND ${CMAKE_COMMAND}
                -E copy_if_different ${DLL} $<TARGET_FILE_DIR:${SECTION_NAME}>
            )
        endforeach (DLL)

        foreach (RESOURCE ${RESOURCES})
            file(RELATIVE_PATH RESOURCE_PATH ${CMAKE_SOURCE_DIR} ${RESOURCE})

            add_custom_command(
                TARGET ${SECTION_NAME}
                PRE_BUILD COMMAND ${CMAKE_COMMAND}
                -E copy_if_different ${RESOURCE} $<TARGET_FILE_DIR:${SECTION_NAME}>/${RESOURCE_PATH}
            )
        endforeach (RESOURCE)
    endforeach (SECTION)
endforeach (CHAPTER)
