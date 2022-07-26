#ifndef LEARN_OPENGL_TEXTURE_H
#define LEARN_OPENGL_TEXTURE_H

class Texture
{
public:
    unsigned int id;
    int type;
    int width;
    int height;
    int channels;

    Texture(int type, const char* path);
    void bind(int unit) const;
private:
    void loadFromFile(const char* path);
};

#endif
