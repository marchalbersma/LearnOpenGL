#version 460 core

uniform vec3 cubeColor;
uniform vec3 lightColor;

out vec4 fragmentColor;

void main()
{
    vec3 ambientColor = 0.1 * lightColor;
    fragmentColor = vec4(cubeColor * ambientColor, 1.0f);
}
