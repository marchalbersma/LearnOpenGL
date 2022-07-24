#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <string>

class Shader
{
public:
    unsigned int Id;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;

private:
    static std::string read(const char* path);
    static unsigned int compile(const char* code, int type);
    static unsigned int link(unsigned int vertex, unsigned int fragment);
};

#endif
