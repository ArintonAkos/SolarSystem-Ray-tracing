#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform vec3 lightDir;

void main()
{
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

  vec3 norm = normalize(Normal);
  vec3 lightDirNorm = normalize(lightDir);
  float diff = max(dot(norm, lightDirNorm), 0.0);
  vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

  vec3 result = (ambient + diffuse) * vec3(texture(texture_diffuse1, TexCoords));
  FragColor = vec4(result, 1.0);
}