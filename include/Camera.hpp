#ifndef LEARN_OPENGL_CAMERA_H
#define LEARN_OPENGL_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Camera
{
public:
    enum Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    explicit Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f
    );
    [[nodiscard]] glm::mat4 getViewMatrix() const;
    void processKeyboard(Movement direction, float deltaTime);
    void processMouseMovement(float x, float y, GLboolean constrainPitch = true);
    void processMouseScroll(float y);
private:
    void updateVectors();
};

#endif
