#define STB_IMAGE_IMPLEMENTATION

#include <Texture.hpp>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>
#include <string>

using namespace std;

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init): properties are initialized by reference
Texture::Texture(const int target, const char* path) : target(target), path(string(path))
{
    glGenTextures(1, &id);
    glBindTexture(target, id);

    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    loadFromFile();
}

Texture::Texture(int target, Type type, const char* path) : Texture(target, path)
{
    this->type = type;
}

void Texture::bind(const int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(target, id);
}

void Texture::setWrap(const int s, const int t) const
{
    glTexParameteri(target, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, t);
}

void Texture::loadFromFile()
{
    stbi_set_flip_vertically_on_load(true);

    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
    const int colors = channels == 4 ? GL_RGBA : GL_RGB;

    if (!image)
    {
        cerr << "Failed to load texture from file " << path << endl;
        exit(-1);
    }

    glTexImage2D(target, 0, colors, width, height, 0, colors, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(target);

    stbi_image_free(image);
}
