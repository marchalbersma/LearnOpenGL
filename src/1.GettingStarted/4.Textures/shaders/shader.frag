#version 460 core

in vec3 vertexColor;
in vec2 textureCoordinates;

uniform sampler2D textureData;

out vec4 fragmentColor;

void main()
{
    fragmentColor = texture(textureData, textureCoordinates) * vec4(vertexColor, 1.0);
}
