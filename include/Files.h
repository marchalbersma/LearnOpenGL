#ifndef LEARN_OPENGL_FILES_H
#define LEARN_OPENGL_FILES_H

namespace Files
{
    const char* getFragmentShaderPath(const char* name);
    const char* getVertexShaderPath(const char* name);
    const char* getFilePath(const char* directory, const char* name, const char* extension);
}

#endif
