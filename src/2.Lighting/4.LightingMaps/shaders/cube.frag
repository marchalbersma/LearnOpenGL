#version 460 core

struct Material
{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 textureCoordinates;

uniform Material material;
uniform Light light;

uniform vec3 cameraPosition;

out vec4 fragmentColor;

void main()
{
    vec3 diffuseTexel = vec3(texture(material.diffuse, textureCoordinates));

    vec3 ambient = light.ambient * diffuseTexel;

    vec3 normal = normalize(fragmentNormal);
    vec3 lightDirection = normalize(light.position - fragmentPosition);
    vec3 diffuse =
        light.diffuse *
        (
            max(dot(normal, lightDirection), 0.0) *
            diffuseTexel
        );

    vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    vec3 specular =
        light.specular *
        (
            pow(max(dot(cameraDirection, reflectDirection), 0.0), material.shininess) *
            material.specular
        );

    fragmentColor = vec4(ambient + diffuse + specular, 1.0);
}
