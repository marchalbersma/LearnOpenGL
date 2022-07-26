#include <FileSystem.hpp>
#include <glad/glad.h>
#include <Glad.hpp>
#include <GLFW.hpp>
#include <glm/glm.hpp>
#include <Shader.hpp>
#include <Texture.hpp>
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
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.3f, 0.5f, 0.0f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.3f, -0.5f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.3f, -0.5f, 0.0f),
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

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates.r));
    glEnableVertexAttribArray(1);

    Texture texture1(GL_TEXTURE_2D, FileSystem::getResourcePath("textures/container.jpg").c_str());
    Texture texture2(GL_TEXTURE_2D, FileSystem::getResourcePath("textures/awesome-face.png").c_str());

    Shader shader("shaders/shader.vert", "shaders/shader.frag");
    shader.use();

    shader.registerUniform("texture1");
    shader.setInt("texture1", 0);

    shader.registerUniform("texture2");
    shader.setInt("texture2", 1);

    GLFW::loop(window, [&]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture1.bind(0);
        texture2.bind(1);

        shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    });
}
