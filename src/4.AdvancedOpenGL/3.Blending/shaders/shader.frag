#version 460 core

in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform sampler2D texture1;

void main()
{
    fragmentColor = texture(texture1, textureCoordinates);
}
