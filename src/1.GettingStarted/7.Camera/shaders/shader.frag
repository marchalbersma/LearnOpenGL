#version 460 core

in vec2 textureCoordinates;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 fragmentColor;

void main()
{
    fragmentColor = mix(
        texture(texture1, textureCoordinates),
        texture(texture2, textureCoordinates),
        0.2
    );
}
