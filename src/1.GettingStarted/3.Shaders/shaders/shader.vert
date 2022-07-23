#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform float time;

out vec3 vertexColor;

const float pi = radians(180);

const float multiplicationValue = 1 / sqrt(3);
const vec3 multiplicationVector = vec3(multiplicationValue, multiplicationValue, multiplicationValue);

vec3 rotateHue(vec3 color, float degrees);

void main()
{
   gl_Position = vec4(position, 1.0);
   vertexColor = rotateHue(color, time * 60);
}

vec3 rotateHue(vec3 color, float degrees)
{
   const float radians = radians(degrees);
   const float sin = sin(radians);
   const float cos = cos(radians);

   return vec3(
      (color * cos) +
      (cross(multiplicationVector, color) * sin) +
      (multiplicationVector * dot(multiplicationVector, color) * (1.0 - cos))
   );
}
