#define GLFW_INCLUDE_NONE

#include <GLFW.h>
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
