#include <glad/glad.h>
#include <Glad.h>
#include <GLFW.h>
#include <Shader.h>

int main()
{
    GLFW::init();
    GLFWwindow* window = GLFW::createWindow(1280, 720);

    Glad::init();

    const float vertices[] = {
        -0.33f, -0.5f,  0.0f,
        0.33f,  -0.5f,  0.0f,
        0.0f,   0.5f,   0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader shader("shader.vert", "shader.frag");

    GLFW::loop(window, []() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });
}
