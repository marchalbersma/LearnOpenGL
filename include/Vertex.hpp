#ifndef LEARN_OPENGL_VERTEX_H
#define LEARN_OPENGL_VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 textureCoordinates;
};

#endif
