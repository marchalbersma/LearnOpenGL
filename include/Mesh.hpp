#ifndef LEARN_OPENGL_MESH_H
#define LEARN_OPENGL_MESH_H

#include <Shader.hpp>
#include <Texture.hpp>
#include <vector>
#include <Vertex.hpp>

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(Shader &shader);
private:
    unsigned int VAO, VBO, EBO;
};

#endif
