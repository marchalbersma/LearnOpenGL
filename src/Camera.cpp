#include <Camera.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init): up & right properties are initialized by updateVectors()
Camera::Camera(vec3 position, vec3 up, float yaw, float pitch) :
    position(position),
    front(vec3(0.0f, 0.0f, -1.0f)),
    worldUp(up),
    yaw(yaw),
    pitch(pitch),
    movementSpeed(5.0f),
    mouseSensitivity(0.1f),
    zoom(45.0f)
{
    updateVectors();
}

mat4 Camera::getViewMatrix() const
{
    return lookAt(position, position + front, up);
}

void Camera::processKeyboard(Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    if (direction == FORWARD) position += front * velocity;
    if (direction == BACKWARD) position -= front * velocity;
    if (direction == LEFT) position -= right * velocity;
    if (direction == RIGHT) position += right * velocity;
    if (direction == UP) position += up * velocity;
    if (direction == DOWN) position -= up * velocity;
}

void Camera::processMouseMovement(float x, float y, GLboolean constrainPitch)
{
    x *= mouseSensitivity;
    y *= mouseSensitivity;

    yaw += x;
    pitch += y;

    if (constrainPitch) pitch = clamp(pitch, -89.0f, 89.0f);

    updateVectors();
}

void Camera::processMouseScroll(float y)
{
    zoom -= y;
    zoom = clamp(zoom, 1.0f, 45.0f);
}

void Camera::updateVectors()
{
    front.x = cos(radians(yaw)) * cos(radians(pitch));
    front.y = sin(radians(pitch));
    front.z = sin(radians(yaw)) * cos(radians(pitch));
    front = normalize(front);

    right = normalize(cross(front, worldUp));
    up = normalize(cross(right, front));
}
