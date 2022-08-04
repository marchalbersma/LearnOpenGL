#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 coordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 textureCoordinates;

void main()
{
   fragmentPosition = vec3(model * vec4(position, 1.0));
   fragmentNormal = mat3(transpose(inverse(model))) * normal;
   textureCoordinates = coordinates;

   gl_Position = projection * view * vec4(fragmentPosition, 1.0);
}
