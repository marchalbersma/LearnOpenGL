#define GLFW_INCLUDE_NONE

#include <GLFW.hpp>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const int GLFW::openGLVersionMajor = 4;
const int GLFW::openGLVersionMinor = 6;

void GLFW::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* GLFW::createWindow(const int width, const int height)
{
    GLFWwindow* window = glfwCreateWindow(width, height, "Learn OpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, const int width, const int height)
    {
        glViewport(0, 0, width, height);
    });

    return window;
}

void GLFW::loop(GLFWwindow* window, const function<void()>& callback)
{
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        callback();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void GLFW::loop(GLFWwindow* window, const function<void(float deltaTime)>& callback)
{
    float lastFrameTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        auto currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        callback(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
