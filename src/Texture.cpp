#define STB_IMAGE_IMPLEMENTATION

#include <Texture.hpp>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>

using namespace std;

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init): properties are initialized by reference
Texture::Texture(const int type, const char* path)
{
    this->type = type;

    glGenTextures(1, &id);
    glBindTexture(type, id);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    loadFromFile(path);
}

void Texture::bind(const int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, id);
}

void Texture::loadFromFile(const char* path)
{
    stbi_set_flip_vertically_on_load(true);

    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);
    const int colors = channels == 4 ? GL_RGBA : GL_RGB;

    if (!image)
    {
        cerr << "Failed to load texture from file " << path << endl;
        exit(-1);
    }

    glTexImage2D(type, 0, colors, width, height, 0, colors, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(type);

    stbi_image_free(image);
}
