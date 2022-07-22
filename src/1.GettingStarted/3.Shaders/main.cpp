#include <Console.h>
#include <Files.h>
#include <glad/glad.h>
#include <Glad.h>
#include <GLFW.h>
#include <Shader.h>

int main()
{
    const char* shaders[] = {
        "fragment-color-from-vertex",
        "fragment-color-from-uniform"
    };

    const char* shaderName = Console::getUserChoice("shader", shaders, 2);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    Shader shader(
        Files::getVertexShaderPath(shaderName),
        Files::getFragmentShaderPath(shaderName)
    );

    int uniformLocation = -1;

    if (strcmp(shaderName, "fragment-color-from-uniform") == 0)
    {
        uniformLocation = glGetUniformLocation(shader.Id, "color");
    }

    GLFW::loop(window, [VAO, shaderName, shader, uniformLocation]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (strcmp(shaderName, "fragment-color-from-uniform") == 0)
        {
            float green = (sin(static_cast<float>(glfwGetTime())) / 2.0f) + 0.5f;
            shader.use();
            glUniform4f(uniformLocation, 0.0f, green, 0.0f, 1.0f);
        }
        else
        {
            shader.use();
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    });
}
