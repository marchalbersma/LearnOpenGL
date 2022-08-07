#ifndef LEARN_OPENGL_TEXTURE_H
#define LEARN_OPENGL_TEXTURE_H

#include <string>

class Texture
{
public:
    enum Type {
        DIFFUSE,
        SPECULAR
    };

    unsigned int id;
    std::string path;
    int target;
    Type type;
    int width;
    int height;
    int channels;

    Texture(int target, const char* path);
    Texture(int target, Type type, const char* path);
    void bind(int unit) const;
    void setWrap(int s, int t) const;
private:
    void loadFromFile();
};

#endif
