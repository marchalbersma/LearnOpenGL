#include <GLFW.h>
#include <GLFW/glfw3.h>

const int GLFW::openGLVersionMajor = 4;
const int GLFW::openGLVersionMinor = 6;

void GLFW::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
