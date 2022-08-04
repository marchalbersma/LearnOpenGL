#version 460 core

#define POINT_LIGHTS 4

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 textureCoordinates;

uniform Material material;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[POINT_LIGHTS];
uniform SpotLight spotLight;

uniform vec3 cameraPosition;

out vec4 fragmentColor;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDirection);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection);
vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection);

void main()
{
    vec3 normal = normalize(fragmentNormal);
    vec3 cameraDirection =  normalize(cameraPosition - fragmentPosition);

    vec3 result = calculateDirectionalLight(directionalLight, normal, cameraDirection);

    for (int i = 0; i < POINT_LIGHTS; i++)
    {
        result += calculatePointLight(pointLights[i], normal, fragmentPosition, cameraDirection);
    }

    result += calculateSpotLight(spotLight, normal, fragmentPosition, cameraDirection);

    fragmentColor = vec4(result, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDirection)
{
    vec3 lightDirection = normalize(-light.direction);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, textureCoordinates));

    vec3 diffuse =
        light.diffuse *
        max(dot(normal, lightDirection), 0.0) *
        vec3(texture(material.diffuse, textureCoordinates));

    vec3 specular =
        light.specular *
        pow(max(dot(cameraDirection, reflectionDirection), 0.0), material.shininess) *
        vec3(texture(material.specular, textureCoordinates));

    return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection)
{
    vec3 lightDirection = normalize(light.position - fragmentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float distance    = length(light.position - fragmentPosition);
    float attenuation =
        1.0 /
        (
            light.constant +
            light.linear * distance +
            light.quadratic * distance * distance
        );

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, textureCoordinates));

    vec3 diffuse =
        light.diffuse *
        max(dot(normal, lightDirection), 0.0) *
        vec3(texture(material.diffuse, textureCoordinates));

    vec3 specular =
        light.specular *
        pow(max(dot(cameraDirection, reflectionDirection), 0.0), material.shininess) *
        vec3(texture(material.specular, textureCoordinates));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection)
{
    vec3 lightDirection = normalize(light.position - fragmentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float distance = length(light.position - fragmentPosition);
    float attenuation =
        1.0 /
        (
            light.constant +
            light.linear * distance +
            light.quadratic * distance * distance
        );

    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, textureCoordinates));

    vec3 diffuse =
        light.diffuse *
        max(dot(normal, lightDirection), 0.0) *
        vec3(texture(material.diffuse, textureCoordinates));

    vec3 specular =
        light.specular *
        pow(max(dot(cameraDirection, reflectionDirection), 0.0), material.shininess) *
        vec3(texture(material.specular, textureCoordinates));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
