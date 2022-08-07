#version 460 core

in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform sampler2D screenTexture;

void main()
{
    fragmentColor = vec4(vec3(1.0 - texture(screenTexture, textureCoordinates)), 1.0);
}
