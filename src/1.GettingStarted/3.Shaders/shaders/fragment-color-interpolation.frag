#version 460 core

out vec4 fragmentColor;

in vec3 vertexColor;

void main()
{
    fragmentColor = vec4(vertexColor, 1.0);
}
