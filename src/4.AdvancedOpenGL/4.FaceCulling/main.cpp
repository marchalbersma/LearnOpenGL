#include <Camera.hpp>
#include <FileSystem.hpp>
#include <glad/glad.h>
#include <Glad.hpp>
#include <GLFW.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <Model.hpp>
#include <optional>
#include <Shader.hpp>

using namespace glm;
using namespace std;

void processKeyboardInput(GLFWwindow* window, float deltaTime);
void processMouseMovement([[maybe_unused]] GLFWwindow* window, double x, double y);
void processMouseScroll([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] double x, double y);

Camera camera(vec3(0.0f, 0.0f, 3.0f));
optional<float> lastPositionX, lastPositionY;

int main()
{
    const unsigned int windowWidth = 1280, windowHeight = 720;

    GLFW::init();
    GLFWwindow* window = GLFW::createWindow(windowWidth, windowHeight);
    glfwSetCursorPosCallback(window, processMouseMovement);
    glfwSetScrollCallback(window, processMouseScroll);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Glad::init();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    const Vertex vertices[] {
        // Front
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },

        // Back
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },

        // Top
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },

        // Bottom
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },

        // Left
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },

        // Right
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));
    glEnableVertexAttribArray(1);

    Texture texture(GL_TEXTURE_2D, FileSystem::getResourcePath("textures/marble.jpg").c_str());

    Shader shader("shaders/shader.vert", "shaders/shader.frag");

    shader.registerUniform("model");
    shader.registerUniform("view");
    shader.registerUniform("projection");

    shader.registerUniform("texture1");

    shader.use();

    shader.setInt("texture1", 0);

    GLFW::loop(window, [&](float time, float deltaTime) {
        processKeyboardInput(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 model;
        const mat4 projection = perspective(
            radians(camera.zoom),
            (float)windowWidth / (float)windowHeight,
            0.1f,
            100.0f
        );
        const mat4 view = camera.getViewMatrix();

        shader.use();

        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        texture.bind(0);

        model = mat4(1.0f);

        shader.setMat4("model", model);
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
