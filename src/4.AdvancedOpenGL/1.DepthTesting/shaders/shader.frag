#version 460 core

in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform sampler2D texture1;

float near = 0.1;
float far  = 100.0;

float linearizeDepth(float depth);

void main()
{
    float depth = linearizeDepth(gl_FragCoord.z) / far;
    fragmentColor = texture(texture1, textureCoordinates) * vec4(vec3(depth), 1.0);
}

float linearizeDepth(float depth)
{
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}
