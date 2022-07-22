#include <Files.h>
#include <cstring>
#include <iostream>

using namespace std;

const char* Files::getFragmentShaderPath(const char* name)
{
    return getFilePath("shaders", name, "frag");
}

const char* Files::getVertexShaderPath(const char* name)
{
    return getFilePath("shaders", name, "vert");
}

const char* Files::getFilePath(const char* directory, const char* name, const char* extension)
{
    const unsigned long length = strlen(directory) + strlen(name) + strlen(extension) + 3;

    char* path = new char[length];
    sprintf(path, "%s/%s.%s", directory, name, extension);

    return path;
}
