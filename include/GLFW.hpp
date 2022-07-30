#ifndef LEARN_OPENGL_GLFW_H
#define LEARN_OPENGL_GLFW_H

#include <functional>
#include <GLFW/glfw3.h>

namespace GLFW
{
    extern const int openGLVersionMajor;
    extern const int openGLVersionMinor;

    void init();
    GLFWwindow* createWindow(int width, int height);
    void loop(GLFWwindow* window, const std::function<void()>& callback);
    void loop(GLFWwindow* window, const std::function<void(float deltaTime)>& callback);
    void loop(GLFWwindow* window, const std::function<void(float time, float deltaTime)>& callback);
}

#endif
