#version 460 core

in vec3 fragmentPosition;
in vec3 fragmentNormal;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cubeColor;

out vec4 fragmentColor;

void main()
{
    vec3 ambientColor = 0.1 * lightColor;

    vec3 normal = normalize(fragmentNormal);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
    vec3 diffuseColor = max(dot(normal, lightDirection), 0.0) * lightColor;

    fragmentColor = vec4(cubeColor * (ambientColor + diffuseColor), 1.0);

}
