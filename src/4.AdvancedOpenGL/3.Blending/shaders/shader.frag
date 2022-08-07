#version 460 core

in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform sampler2D texture1;

void main()
{
    vec4 texel = texture(texture1, textureCoordinates);

    if(texel.a < 0.1)
    {
        discard;
    }

    fragmentColor = texel;
}
