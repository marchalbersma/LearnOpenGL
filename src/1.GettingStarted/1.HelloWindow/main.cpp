#include <Glad.h>
#include <GLFW.h>

int main()
{
    GLFW::init();
    GLFW::createWindow(1280, 720);

    Glad::init();
}
