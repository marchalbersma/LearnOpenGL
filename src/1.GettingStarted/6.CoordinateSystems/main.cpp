#include <FileSystem.hpp>
#include <glad/glad.h>
#include <Glad.hpp>
#include <GLFW.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader.hpp>
#include <Texture.hpp>
#include <Vertex.hpp>

using namespace glm;
using namespace std;

int main()
{
    const unsigned int windowWidth = 1280, windowHeight = 720;

    GLFW::init();
    GLFWwindow* window = GLFW::createWindow(windowWidth, windowHeight);

    Glad::init();

    const Vertex vertices[] {
        // Front
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
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
                .position = vec3(-0.5f, 0.5f, -0.5f),
                .textureCoordinates = vec2(0.0f, 1.0f)
        },
        Vertex {
                .position = vec3(0.5f, 0.5f, -0.5f),
                .textureCoordinates = vec2(1.0f, 1.0f)
        },

        // Bottom
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
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
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(-0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(-0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },

        // Right
        Vertex {
            .position = vec3(0.5f, 0.5f, 0.5f),
            .textureCoordinates = vec2(1.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, 0.5f),
            .textureCoordinates = vec2(0.0f, 0.0f)
        },
        Vertex {
            .position = vec3(0.5f, 0.5f, -0.5f),
            .textureCoordinates = vec2(1.0f, 1.0f)
        },
        Vertex {
            .position = vec3(0.5f, -0.5f, -0.5f),
            .textureCoordinates = vec2(0.0f, 1.0f)
        },
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position.x));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates.r));
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);

    Texture texture1(GL_TEXTURE_2D, FileSystem::getResourcePath("textures/container.jpg").c_str());
    Texture texture2(GL_TEXTURE_2D, FileSystem::getResourcePath("textures/awesome-face.png").c_str());

    mat4 view = mat4(1.0f), projection;

    view = translate(view, vec3(0.0f, 0.0f, -3.0f));
    projection = perspective(
        radians(45.0f),
        (float)windowWidth / (float)windowHeight,
        0.1f,
        100.0f
    );

    Shader shader("shaders/shader.vert", "shaders/shader.frag");
    shader.use();

    shader.registerUniform("model");

    shader.registerUniform("view");
    shader.setMat4("view", view);

    shader.registerUniform("projection");
    shader.setMat4("projection", projection);

    shader.registerUniform("texture1");
    shader.setInt("texture1", 0);

    shader.registerUniform("texture2");
    shader.setInt("texture2", 1);

    GLFW::loop(window, [&]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture1.bind(0);
        texture2.bind(1);

        mat4 model = mat4(1.0f);
        model = rotate(model, (float)glfwGetTime(), vec3(1.0f, 0.5f, 0.25f));
        shader.setMat4("model", model);

        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
    });
}
