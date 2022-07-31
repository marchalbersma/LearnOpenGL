#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragmentPosition;
out vec3 fragmentNormal;

void main()
{
   fragmentPosition = vec3(model * vec4(position, 1.0));
   fragmentNormal = normal;

   gl_Position = projection * view * vec4(fragmentPosition, 1.0);
}
