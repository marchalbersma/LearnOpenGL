#define STB_IMAGE_IMPLEMENTATION

#include <FileSystem.hpp>
#include <glad/glad.h>
#include <Glad.hpp>
#include <GLFW.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <Shader.hpp>
#include <stb/stb_image.h>
#include <string>
#include <Vertex.hpp>

using namespace glm;
using namespace std;

int main()
{
    GLFW::init();
    GLFWwindow* window = GLFW::createWindow(1280, 720);

    Glad::init();

    const Vertex vertices[] {
        Vertex {
            .position = vec3(-0.3f, 0.5f, 0.0f),
            .color = vec3(1.0f, 1.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.3f, 0.5f, 0.0f),
            .color = vec3(1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.3f, -0.5f, 0.0f),
            .color = vec3(0.0f, 1.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.3f, -0.5f, 0.0f),
            .color = vec3(0.0f, 0.0f, 1.0f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        }
    };

    const unsigned int indices[] {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position.x));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color.r));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates.x));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const string texturePath = FileSystem::getResourcePath("textures/container.jpg");

    int textureWidth, textureHeight, textureChannels;
    unsigned char* textureData = stbi_load(
            texturePath.c_str(),
            &textureWidth,
            &textureHeight,
            &textureChannels,
            0
    );

    if (!textureData)
    {
        cerr << "Failed to load texture " << texturePath << endl;
        exit(-1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0);

    stbi_image_free(textureData);

    Shader shader("shaders/shader.vert", "shaders/shader.frag");

    GLFW::loop(window, [VAO, texture, shader]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    });
}
