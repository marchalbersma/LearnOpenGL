#version 460 core

in vec3 vertexColor;
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
    ) * vec4(vertexColor, 1.0);
}
