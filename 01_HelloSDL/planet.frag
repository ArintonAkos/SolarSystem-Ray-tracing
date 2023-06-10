#version 460 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};


struct Light {
    vec3 position;

    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse;
uniform Light light;

uniform float shininess = 0.5;


vec3 calcPointLight(Light light, vec3 Normal, vec3 FragPos, vec3 viewDir) {

    vec3 lightDir = normalize(light.position - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);

    float diff = max(dot(Normal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));

    vec3 ambient = light.ambient  * vec3(texture(texture_diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_diffuse, TexCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

void main() {
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);

    vec3 result = calcPointLight(light, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}