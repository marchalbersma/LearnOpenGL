#ifndef LEARN_OPENGL_GLFW_H
#define LEARN_OPENGL_GLFW_H

#include <GLFW/glfw3.h>

namespace GLFW
{
    extern const int openGLVersionMajor;
    extern const int openGLVersionMinor;

    void init();
    GLFWwindow* createWindow(int width, int height);
}

#endif
