#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
    unsigned int id;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void registerUniform(const std::string& name);
    void setFloat(const std::string& uniformName, float value) const;
    void setInt(const std::string& uniformName, int value) const;
    void setMat4(const std::string& uniformName, const glm::mat4& matrix) const;
private:
    std::unordered_map<std::string, int> uniforms;

    static std::string read(const char* path);
    static unsigned int compile(const char* code, int type);
    static unsigned int link(unsigned int vertex, unsigned int fragment);
};

#endif
