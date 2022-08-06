#ifndef LEARN_OPENGL_MODEL_H
#define LEARN_OPENGL_MODEL_H

#include <assimp/scene.h>
#include <Shader.hpp>
#include <string>
#include <Mesh.hpp>
#include <Texture.hpp>

class Model
{
public:
    explicit Model(const std::string& path);
    void draw(Shader &shader);
private:
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;
    std::string directory;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType aiType, Texture::Type type);
};

#endif
