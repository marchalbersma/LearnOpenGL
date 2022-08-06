#version 460 core

struct Material
{
    sampler2D textureDiffuse1;
    sampler2D textureSpecular1;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform vec3 cameraPosition;
uniform Material material;
uniform DirectionalLight directionalLight;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDirection);

void main()
{
    vec3 normal = normalize(fragmentNormal);
    vec3 cameraDirection =  normalize(cameraPosition - fragmentPosition);

    fragmentColor = vec4(calculateDirectionalLight(directionalLight, normal, cameraDirection), 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDirection)
{
    vec3 lightDirection = normalize(-light.direction);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    vec3 ambient = light.ambient * vec3(texture(material.textureDiffuse1, textureCoordinates));

    vec3 diffuse =
    light.diffuse *
    max(dot(normal, lightDirection), 0.0) *
    vec3(texture(material.textureDiffuse1, textureCoordinates));

    vec3 specular =
    light.specular *
    pow(max(dot(cameraDirection, reflectionDirection), 0.0), 32.0) *
    vec3(texture(material.textureSpecular1, textureCoordinates));

    return (ambient + diffuse + specular);
}