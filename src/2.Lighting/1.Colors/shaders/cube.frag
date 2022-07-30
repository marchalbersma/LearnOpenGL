#version 460 core

uniform vec3 cubeColor;
uniform vec3 lightColor;

out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(cubeColor * lightColor, 1.0f);
}
