#include <glad/glad.h>
#include <Glad.hpp>
#include <GLFW.hpp>

int main()
{
    GLFW::init();
    GLFWwindow* window = GLFW::createWindow(1280, 720);

    Glad::init();

    GLFW::loop(window, []() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });
}
