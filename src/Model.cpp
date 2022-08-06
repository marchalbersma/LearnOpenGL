#include <Model.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <Mesh.hpp>
#include <Shader.hpp>
#include <string>
#include <Texture.hpp>

using namespace Assimp;
using namespace glm;
using namespace std;

Model::Model(const string& path)
{
    Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cerr << "Failed to load model " << path << endl << importer.GetErrorString() << endl;
        exit(-1);
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::draw(Shader &shader)
{
    for (Mesh mesh : meshes)
    {
        mesh.draw(shader);
    }
}

void Model::processNode(aiNode* node, const aiScene* scene) // NOLINT(misc-no-recursion)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex { };

        vertex.position = vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        vertex.normal = vec3(
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        );

        if (mesh->mTextureCoords[0])
        {
            vertex.textureCoordinates = vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else
        {
            vertex.textureCoordinates = vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(mesh->mFaces[i].mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        vector<Texture> diffuseMaps = loadMaterialTextures(
            material,
            aiTextureType_DIFFUSE,
            Texture::Type::DIFFUSE
        );
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        vector<Texture> specularMaps = loadMaterialTextures(
            material,
            aiTextureType_SPECULAR,
            Texture::Type::SPECULAR
        );
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return { vertices, indices, textures };
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType aiType, Texture::Type type)
{
    vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(aiType); i++)
    {
        aiString fileName;
        material->GetTexture(aiType, i, &fileName);
        string path = directory + '/' + string(fileName.C_Str());

        bool loaded = false;
        for (const Texture& texture : loadedTextures)
        {
            if (texture.path == path)
            {
                textures.push_back(texture);
                loaded = true;
                break;
            }
        }

        if (!loaded)
        {
            Texture texture(GL_TEXTURE_2D, type, path.c_str());
            textures.push_back(texture);
            loadedTextures.push_back(texture);
        }
    }

    return textures;
}
