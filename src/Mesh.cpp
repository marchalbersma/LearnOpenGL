#include <Mesh.hpp>
#include <glad/glad.h>
#include <string>
#include <Shader.hpp>
#include <Texture.hpp>
#include <utility>
#include <vector>
#include <Vertex.hpp>

using namespace std;

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init): VAO, VBO & EBO properties are initialized by reference
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) :
    vertices(vertices), indices(indices), textures(std::move(textures))
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(Vertex)), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(indices.size() * sizeof(unsigned int)), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

    glBindVertexArray(0);
}

void Mesh::draw(Shader& shader)
{
    unsigned int diffuseCount = 1;
    unsigned int specularCount = 1;

    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        string name = "material.texture";

        switch (textures[i].type)
        {
            case Texture::Type::DIFFUSE:
                name.append("Diffuse");
                name.append(to_string(diffuseCount));
                diffuseCount++;
                break;
            case Texture::Type::SPECULAR:
                name.append("Specular");
                name.append(to_string(specularCount));
                specularCount++;
                break;
        }

        textures[i].bind(i);
        shader.registerUniform(name);
        shader.setInt(name, i);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
