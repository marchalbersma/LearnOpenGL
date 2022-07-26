#version 460 core

in vec3 vertexColor;
in vec2 textureCoordinates;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;
uniform float size;
uniform float time;

out vec4 fragmentColor;

vec2 rotate(vec2 value, vec2 origin, float angle);

void main()
{
    vec4 texel1 = texture(texture1, textureCoordinates);
    vec4 texel2 = texture(texture2, rotate(textureCoordinates / size, vec2(0.5, 0.5) / size, time));

    fragmentColor = mix(
        texel1,
        mix(texel1, texel2, texel2.a),
        mixValue
    ) * vec4(vertexColor, 1.0);
}

vec2 rotate(vec2 value, vec2 origin, float angle) {
    float sin = sin(angle);
    float cos = cos(angle);

    value -= origin;
    value = mat2(cos, -sin, sin, cos) * value;
    value += origin;

    return value;
}
