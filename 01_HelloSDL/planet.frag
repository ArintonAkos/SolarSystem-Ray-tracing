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

struct Planet {
    vec3 position;
    float radius;
};

struct Camera {
    vec3 position;
    vec3 frontAxis;
    vec3 upAxis;
    vec3 sideAxis;
    vec2 fov;
    float width;
    float height;
};

struct Ray {
    vec3 startPos;
	vec3 direction;
};

struct IntersectedPlanet {
	Planet planet;
	float t;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse;
uniform Light light;
uniform Camera camera; 
uniform Planet planets[9];
uniform int planetCount;  
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

float intersect (Ray ray, Planet planet) {
	vec3 oc = ray.startPos - planet.position;
	float a = dot(ray.direction, ray.direction);
	float b = 2.0 * dot(oc, ray.direction);
	float c = - planet.radius * planet.radius;
	float delta = b * b - (4.0 * a * c);
	
    if (delta < 0.0) {
        return -1.0;
    }
    else if (delta == 0.0) {
		float t =  (-b + sqrt(delta)) / (2.0 * a);
        if (t > 0.0) {
			return t;
		}
		else {
			return -1.0;
		}
	}
	else {
		float t1 = (-b - sqrt(delta)) / (2.0 * a);
		float t2 = (-b + sqrt(delta)) / (2.0 * a);
		float tMin =  min(t1, t2);
        if (tMin > 0.0) {
            return tMin;
		}
		else {
			return -1.0;
		}
	}

}

IntersectedPlanet firstIntersection(Ray ray) {
    float tMin = -1.0;
    IntersectedPlanet firstPlanetIntersected;

    for(int i = 0; i < planetCount; i++) {
        float t = intersect(ray, planets[i]);
            if((t > 0.0 && t < tMin) || tMin == -1.0) {
            firstPlanetIntersected.t = t;
			firstPlanetIntersected.planet = planets[i];
			tMin = t;
		}
    }
    return firstPlanetIntersected;
}

void main() {
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);
    
    vec3 result = calcPointLight(light, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}