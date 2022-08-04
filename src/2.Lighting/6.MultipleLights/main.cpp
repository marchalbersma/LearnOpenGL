#include <Camera.hpp>
#include <FileSystem.hpp>
#include <glad/glad.h>
#include <Glad.hpp>
#include <GLFW.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <optional>
#include <Shader.hpp>
#include <Texture.hpp>
#include <Vertex.hpp>
#include <random>

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
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .normal = vec3(0.0f, 0.0f, 1.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .normal = vec3(0.0f, 0.0f, 1.0f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .normal = vec3(0.0f, 0.0f, 1.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .normal = vec3(0.0f, 0.0f, 1.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .normal = vec3(0.0f, 0.0f, 1.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .normal = vec3(0.0f, 0.0f, 1.0f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },

        // Back
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .normal = vec3(0.0f, 0.0f, -1.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .normal = vec3(0.0f, 0.0f, -1.0f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .normal = vec3(0.0f, 0.0f, -1.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .normal = vec3(0.0f, 0.0f, -1.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .normal = vec3(0.0f, 0.0f, -1.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .normal = vec3(0.0f, 0.0f, -1.0f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },

        // Top
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .normal = vec3(0.0f, 1.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .normal = vec3(0.0f, 1.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .normal = vec3(0.0f, 1.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .normal = vec3(0.0f, 1.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .normal = vec3(0.0f, 1.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .normal = vec3(0.0f, 1.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },

        // Bottom
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .normal = vec3(0.0f, -1.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .normal = vec3(0.0f, -1.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .normal = vec3(0.0f, -1.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .normal = vec3(0.0f, -1.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .normal = vec3(0.0f, -1.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .normal = vec3(0.0f, -1.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },

        // Left
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .normal = vec3(-1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .normal = vec3(-1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .normal = vec3(-1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .normal = vec3(-1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .normal = vec3(-1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .normal = vec3(-1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },

        // Right
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .normal = vec3(1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .normal = vec3(1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .normal = vec3(1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .normal = vec3(1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .normal = vec3(1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .normal = vec3(1.0f, 0.0f, 0.0f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
    };

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position.x));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal.x));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates.x));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position.x));
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);

    Texture diffuse(GL_TEXTURE_2D, FileSystem::getResourcePath("textures/crate.png").c_str());
    Texture specular(GL_TEXTURE_2D, FileSystem::getResourcePath("textures/crate-specular.png").c_str());

    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    Shader cubeShader("shaders/cube.vert", "shaders/cube.frag");
    cubeShader.use();

    mat4 cubeModel = mat4(1.0f);

    cubeShader.registerUniform("model");
    cubeShader.setMat4("model", cubeModel);

    cubeShader.registerUniform("view");
    cubeShader.registerUniform("projection");

    cubeShader.registerUniform("material.diffuse");
    cubeShader.registerUniform("material.specular");
    cubeShader.registerUniform("material.shininess");

    cubeShader.setInt("material.diffuse", 0);
    cubeShader.setInt("material.specular", 1);
    cubeShader.setFloat("material.shininess", 32.0f);

    cubeShader.registerUniform("directionalLight.direction");
    cubeShader.registerUniform("directionalLight.ambient");
    cubeShader.registerUniform("directionalLight.diffuse");
    cubeShader.registerUniform("directionalLight.specular");

    for (unsigned int j = 0; j < 4; j++)
    {
        string number = to_string(j);

        cubeShader.registerUniform("pointLights[" + number + "].position");
        cubeShader.registerUniform("pointLights[" + number + "].ambient");
        cubeShader.registerUniform("pointLights[" + number + "].diffuse");
        cubeShader.registerUniform("pointLights[" + number + "].specular");
        cubeShader.registerUniform("pointLights[" + number + "].constant");
        cubeShader.registerUniform("pointLights[" + number + "].linear");
        cubeShader.registerUniform("pointLights[" + number + "].quadratic");
    }

    cubeShader.registerUniform("spotLight.position");
    cubeShader.registerUniform("spotLight.direction");
    cubeShader.registerUniform("spotLight.ambient");
    cubeShader.registerUniform("spotLight.diffuse");
    cubeShader.registerUniform("spotLight.specular");
    cubeShader.registerUniform("spotLight.constant");
    cubeShader.registerUniform("spotLight.linear");
    cubeShader.registerUniform("spotLight.quadratic");
    cubeShader.registerUniform("spotLight.cutOff");
    cubeShader.registerUniform("spotLight.outerCutOff");

    cubeShader.registerUniform("cameraPosition");

    Shader lightShader("shaders/light.vert", "shaders/light.frag");
    lightShader.use();

    lightShader.registerUniform("model");
    lightShader.registerUniform("view");
    lightShader.registerUniform("projection");

    lightShader.registerUniform("color");

    random_device randomDevice;
    mt19937 randomGenerator(randomDevice());

    uniform_real_distribution<float> xDistribution(-3.0f, 3.0f);
    uniform_real_distribution<float> yDistribution(-1.5f, 1.5f);
    uniform_real_distribution<float> zDistribution(-12.0f, 0.0f);
    uniform_real_distribution<float> rotationDistribution(0.0f, 1.0f);

    vec3 cubePositions[10], cubeRotations[10];
    for (unsigned int i = 0; i < 10; i++)
    {
        cubePositions[i] = vec3(
            xDistribution(randomGenerator),
            yDistribution(randomGenerator),
            zDistribution(randomGenerator)
        );

        cubeRotations[i] = vec3(
            rotationDistribution(randomGenerator),
            rotationDistribution(randomGenerator),
            rotationDistribution(randomGenerator)
        );
    }

    vec3 pointLightPositions[] = {
        vec3( 0.7f,  0.2f,  2.0f),
        vec3( 2.3f, -3.3f, -4.0f),
        vec3(-4.0f,  2.0f, -12.0f),
        vec3( 0.0f,  0.0f, -3.0f)
    };

    vec3 pointLightColors[] = {
        vec3(1.0f, 0.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f),
        vec3(0.0f, 0.0f, 1.0f),
        vec3(1.0f, 1.0f, 0.0f)
    };

    GLFW::loop(window, [&](float time, float deltaTime) {
        processKeyboardInput(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        diffuse.bind(0);
        specular.bind(1);

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
        cubeShader.setVec3("cameraPosition", camera.position);

        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            mat4 model = mat4(1.0f);
            model = translate(model, cubePositions[i]);
            model = rotate(model, time, cubeRotations[i]);

            cubeShader.setMat4("model", model);

            cubeShader.setVec3("directionalLight.direction", vec3(-0.2f, -1.0f, -0.3f));
            cubeShader.setVec3("directionalLight.ambient", lightColor * 0.05f);
            cubeShader.setVec3("directionalLight.diffuse", lightColor * 0.4f);
            cubeShader.setVec3("directionalLight.specular", lightColor * 0.5f);

            for (unsigned int j = 0; j < 4; j++)
            {
                string number = to_string(j);

                cubeShader.setVec3("pointLights[" + number + "].position", pointLightPositions[j]);
                cubeShader.setVec3("pointLights[" + number + "].ambient", pointLightColors[j] * 0.05f);
                cubeShader.setVec3("pointLights[" + number + "].diffuse", pointLightColors[j] * 0.8f);
                cubeShader.setVec3("pointLights[" + number + "].specular", vec3(1.0f, 1.0f, 1.0f));
                cubeShader.setFloat("pointLights[" + number + "].constant", 1.0f);
                cubeShader.setFloat("pointLights[" + number + "].linear", 0.09f);
                cubeShader.setFloat("pointLights[" + number + "].quadratic", 0.032f);
            }

            cubeShader.setVec3("spotLight.position", camera.position);
            cubeShader.setVec3("spotLight.direction", camera.front);
            cubeShader.setVec3("spotLight.ambient", vec3(0.0f, 0.0f, 0.0f));
            cubeShader.setVec3("spotLight.diffuse", lightColor);
            cubeShader.setVec3("spotLight.specular", lightColor);
            cubeShader.setFloat("spotLight.constant", 1.0f);
            cubeShader.setFloat("spotLight.linear", 0.09f);
            cubeShader.setFloat("spotLight.quadratic", 0.032f);
            cubeShader.setFloat("spotLight.cutOff", cos(radians(12.5f)));
            cubeShader.setFloat("spotLight.outerCutOff", cos(radians(15.0f)));

            glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
        }

        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);

        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            mat4 model = mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, vec3(0.2f));

            lightShader.setMat4("model", model);
            lightShader.setVec3("color", pointLightColors[i]);

            glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
        }
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
