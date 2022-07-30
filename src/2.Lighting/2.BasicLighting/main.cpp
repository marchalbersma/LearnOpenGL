#include <Camera.hpp>
#include <glad/glad.h>
#include <Glad.hpp>
#include <GLFW.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <optional>
#include <Shader.hpp>
#include <Vertex.hpp>

using namespace glm;
using namespace std;

void processKeyboardInput(GLFWwindow* window, float deltaTime);
void processMouseMovement([[maybe_unused]] GLFWwindow* window, double x, double y);
void processMouseScroll([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] double x, double y);

Camera camera(vec3(0.0f, 0.0f, 3.0f));
optional<float> lastPositionX;
optional<float> lastPositionY;

int main()
{
    const unsigned int windowWidth = 1280, windowHeight = 720;

    GLFW::init();
    GLFWwindow* window = GLFW::createWindow(windowWidth, windowHeight);
    glfwSetCursorPosCallback(window, processMouseMovement);
    glfwSetScrollCallback(window, processMouseScroll);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Glad::init();

    const Vertex vertices[] {
        // Front
        Vertex { .position = vec3(-0.5f, 0.5f, 0.5f) },
        Vertex { .position = vec3(0.5f, 0.5f, 0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, 0.5f, 0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, -0.5f, 0.5f) },

        // Back
        Vertex { .position = vec3(-0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, -0.5f) },
        Vertex { .position = vec3(-0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, -0.5f) },
        Vertex { .position = vec3(-0.5f, -0.5f, -0.5f) },

        // Top
        Vertex { .position = vec3(-0.5f, 0.5f, 0.5f) },
        Vertex { .position = vec3(0.5f, 0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, 0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, 0.5f, -0.5f) },

        // Bottom
        Vertex { .position = vec3(-0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, -0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, -0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, -0.5f) },

        // Left
        Vertex { .position = vec3(-0.5f, 0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(-0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(-0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(-0.5f, -0.5f, -0.5f) },

        // Right
        Vertex { .position = vec3(0.5f, 0.5f, 0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, 0.5f) },
        Vertex { .position = vec3(0.5f, 0.5f, -0.5f) },
        Vertex { .position = vec3(0.5f, -0.5f, -0.5f) },
    };

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position.x));
    glEnableVertexAttribArray(0);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position.x));
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);

    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 cubeColor = vec3(1.0f, 0.5f, 0.31f);

    Shader cubeShader("shaders/cube.vert", "shaders/cube.frag");
    cubeShader.use();

    mat4 cubeModel = mat4(1.0f);

    cubeShader.registerUniform("model");
    cubeShader.setMat4("model", cubeModel);

    cubeShader.registerUniform("view");
    cubeShader.registerUniform("projection");

    cubeShader.registerUniform("cubeColor");
    cubeShader.setVec3("cubeColor", cubeColor);

    cubeShader.registerUniform("lightColor");
    cubeShader.setVec3("lightColor", lightColor);

    Shader lightShader("shaders/light.vert", "shaders/light.frag");
    lightShader.use();

    mat4 lightModel = mat4(1.0f);
    lightModel = translate(lightModel, vec3(1.2f, 1.0f, 2.0f));
    lightModel = scale(lightModel, vec3(0.2f));

    lightShader.registerUniform("model");
    lightShader.setMat4("model", lightModel);

    lightShader.registerUniform("view");
    lightShader.registerUniform("projection");

    lightShader.registerUniform("color");
    lightShader.setVec3("color", lightColor);

    GLFW::loop(window, [&](float deltaTime) {
        processKeyboardInput(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const mat4 projection = perspective(
            radians(camera.zoom),
            (float)windowWidth / (float)windowHeight,
            0.1f,
            100.0f
        );
        const mat4 view = camera.getViewMatrix();

        cubeShader.use();
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));

        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
    });
}

void processKeyboardInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(Camera::Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(Camera::Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(Camera::Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(Camera::Movement::RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(Camera::Movement::UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.processKeyboard(Camera::Movement::DOWN, deltaTime);
}

void processMouseMovement([[maybe_unused]] GLFWwindow* window, double x, double y)
{
    auto positionX = static_cast<float>(x), positionY = static_cast<float>(y);

    if (!lastPositionX.has_value() || !lastPositionY.has_value())
    {
        lastPositionX = positionX;
        lastPositionY = positionY;
    }

    float offsetX = positionX - lastPositionX.value();
    float offsetY = lastPositionY.value() - positionY;

    lastPositionX = positionX;
    lastPositionY = positionY;

    camera.processMouseMovement(offsetX, offsetY);
}

void processMouseScroll([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] double x, double y)
{
    camera.processMouseScroll(static_cast<float>(y));
}
