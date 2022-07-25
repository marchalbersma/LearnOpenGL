#include <glad/glad.h>
#include <Glad.hpp>
#include <GLFW.hpp>
#include <Shader.hpp>
#include <Vertex.hpp>
#include <glm/glm.hpp>

using namespace glm;

int main()
{
    GLFW::init();
    GLFWwindow* window = GLFW::createWindow(1280, 720);

    Glad::init();

    const Vertex vertices[] {
        Vertex {
            .position = vec3(0.33f, -0.5f, 0.0f),
            .color = vec3(1.0f, 0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.33f, -0.5f, 0.0f),
            .color = vec3(0.0f, 1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.0f, 0.5f, 0.0f),
            .color = vec3(0.0f, 0.0f, 1.0f)
        }
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position.x));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color.x));
    glEnableVertexAttribArray(1);

    Shader shader("shaders/shader.vert", "shaders/shader.frag");
    shader.registerUniform("time");

    GLFW::loop(window, [VAO, shader]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setFloat("time", static_cast<float>(glfwGetTime()));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    });
}
