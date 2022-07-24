#include <Shader.hpp>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    id = link(
        compile(read(vertexPath).c_str(), GL_VERTEX_SHADER),
        compile(read(fragmentPath).c_str(), GL_FRAGMENT_SHADER)
    );
}

void Shader::use() const
{
    glUseProgram(id);
}

void Shader::registerUniform(const string& name)
{
    int location = glGetUniformLocation(id, name.c_str());

    if (location == -1)
    {
        cerr << "Failed to find uniform " << name << endl;
        exit(-1);
    }

    uniforms.insert(make_pair(name, location));
}

void Shader::setFloat(const string& uniformName, float value) const
{
    glUniform1f(uniforms.at(uniformName), value);
}

string Shader::read(const char* path)
{
    string code;
    ifstream file;

    file.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        stringstream stream;

        file.open(path);
        stream << file.rdbuf();
        file.close();

        code = stream.str();
    }
    catch (ifstream::failure& exception)
    {
        cerr << "Failed to read shader file " << path << endl << exception.what() << endl;
        exit(-1);
    }

    return code;
}

unsigned int Shader::compile(const char* code, int type)
{
    int success;
    char log[1024];

    const unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        cerr << "Failed to compile shader of type 0x" << hex << uppercase << type << endl << log << endl;
        exit(-1);
    }

    return shader;
}

unsigned int Shader::link(unsigned int vertex, unsigned int fragment)
{
    int success;
    char log[1024];

    const unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 1024, nullptr, log);
        cerr << "Failed to link shaders" << endl << log << endl;
        exit(-1);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}
