#version 460 core

in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0;

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,   offset),
        vec2( 0.0f,     offset),
        vec2( offset,   offset),
        vec2(-offset,   0.0f),
        vec2( 0.0f,     0.0f),
        vec2( offset,   0.0f),
        vec2(-offset,  -offset),
        vec2( 0.0f,    -offset),
        vec2( offset,  -offset)
    );

    float kernel[9] = float[](
        1.0 / 16,   2.0 / 16,   1.0 / 16,
        2.0 / 16,   4.0 / 16,   2.0 / 16,
        1.0 / 16,   2.0 / 16,   1.0 / 16
    );

    vec3 sampleTexture[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTexture[i] = vec3(texture(screenTexture, textureCoordinates.st + offsets[i]));
    }

    vec3 color = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        color += sampleTexture[i] * kernel[i];
    }

    fragmentColor = vec4(color, 1.0);
}
