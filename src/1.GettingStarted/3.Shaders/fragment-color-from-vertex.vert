#version 460 core

layout (location = 0) in vec3 position;

out vec4 vertexColor;

void main()
{
   gl_Position = vec4(position.x, position.y, position.z, 1.0);
   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}
