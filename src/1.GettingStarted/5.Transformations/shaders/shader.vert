#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 coordinates;

out vec2 textureCoordinates;

void main()
{
   gl_Position = vec4(position, 1.0);
   textureCoordinates = coordinates;
}
