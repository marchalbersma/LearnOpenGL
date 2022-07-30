#version 460 core

in vec3 fragmentPosition;
in vec3 fragmentNormal;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;

uniform vec3 cubeColor;
uniform vec3 lightColor;

out vec4 fragmentColor;

void main()
{
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 ambientColor = ambientStrength * lightColor;

    vec3 normal = normalize(fragmentNormal);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
    vec3 diffuseColor = max(dot(normal, lightDirection), 0.0) * lightColor;

    vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    vec3 specularColor = specularStrength * pow(max(dot(cameraDirection, reflectionDirection), 0.0), 32) * lightColor;

    fragmentColor = vec4(cubeColor * (ambientColor + diffuseColor + specularColor), 1.0);

}
