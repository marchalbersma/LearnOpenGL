#version 460 core

in vec2 textureCoordinates;

uniform sampler2D textureData;

out vec4 fragmentColor;

void main()
{
    fragmentColor = texture(textureData, textureCoordinates);
}
