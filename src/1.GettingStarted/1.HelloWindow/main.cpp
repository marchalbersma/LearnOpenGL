#include <Glad.h>
#include <GLFW.h>

int main()
{
    GLFW::init();
    GLFWwindow* window = GLFW::createWindow(1280, 720);

    Glad::init();

    GLFW::loop(window, []() {});
}
