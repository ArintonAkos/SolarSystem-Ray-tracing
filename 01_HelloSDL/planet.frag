#version 460 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float shininess;
};

struct Light
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient; 
    vec3 diffuse;
    vec3 specular;
};

struct Ray 
{
    vec3 startPos;
	vec3 direction;
};

struct Camera 
{
    vec3 position;
    
    vec3 frontAxis;
    vec3 sideAxis;
    vec3 upAxis;

    float fov;
    float width;
    float height;
};

struct Planet
{
    vec3 position;
    float radius;

    int materialIndex;
};

struct Intersection 
{
	float t;
	int planetIndex;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse;

// uniform Light light;
uniform Camera camera; 

uniform Planet planets[9];
uniform int planetCount;  

uniform Light lights[4];
uniform int lightCount;

uniform Material materials[9];
uniform int materialCount;

// uniform float shininess = 0.5;
uniform int maxDepth = 5;
uniform vec3 worldAmbient;

/* vec3 calcPointLight(Light light, vec3 Normal, vec3 FragPos, vec3 viewDir)
{
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
} */

float intersect (Ray ray, Planet planet)
{
    vec3 oc = ray.startPos - planet.position;

	float a = dot(ray.direction, ray.direction);
	float b = 2.0 * dot(ray.direction, oc);
	float c = dot(oc, oc) - planet.radius * planet.radius;
	
    float delta = b * b - 4.0 * a * c;
	
    if (delta < 0.0)
        return -1.0;
    if (delta == 0.0)
        return (-b - sqrt(delta)) / (2.0 * a);
    
    float t1 = (-b - sqrt(delta)) / (2.0 * a);
    float t2 = (-b + sqrt(delta)) / (2.0 * a);

    if (t1 > t2)
    {
        t1 = t1 + t2;
        t2 = t1 - t2;
        t1 = t1 - t2;
    }

    if (t1 >= 0)
        return t1;
    if (t2 >= 0)
        return t2;
    
    return -1.0;
}

Intersection firstIntersection(Ray ray) 
{
    float tMin = -1.0;
    Intersection firstPlanetIntersected;

    for(int i = 0; i < planetCount; ++i) {
        
        float t = intersect(ray, planets[i]);
        
        if(t >= 0.0 && (t < tMin || tMin == -1.0)) 
        {
		    tMin = t;
            
            firstPlanetIntersected.t = t;
		    firstPlanetIntersected.planetIndex = i;
		}
    }

    return firstPlanetIntersected;
}

vec3 calculateLighting(Ray ray, Planet hitPlanet, Material hitMaterial, vec3 intersectionPoint, vec3 hitNormal)
{
    float epsilon = 0.0001;
    vec3 outColor = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < lightCount; i++) 
	{
        Ray shadowRay;
        shadowRay.startPos = intersectionPoint + epsilon * hitNormal;
        shadowRay.direction = normalize(lights[i].position - intersectionPoint);
                        
        float cosTheta = dot(hitNormal, shadowRay.direction);

        if (cosTheta > 0.0)
	    {
		    float t = intersect(shadowRay, hitPlanet);
		    if (t > 0.0)
		    {
			    outColor += hitMaterial.ambient * lights[i].ambient * cosTheta;
                vec3 halfway = normalize(shadowRay.direction - ray.direction);
                float cosDelta = dot(hitNormal, halfway);

                if (cosDelta > 0.0)
			    {
				    outColor += hitMaterial.specular * lights[i].specular * pow(cosDelta, hitMaterial.shininess);
			    }
		    }
	    }
    }

    return outColor;
}

vec3 trace (Ray ray)
{
    const float epsilon = 0.0001;
    vec3 outColor = vec3(0.0, 0.0, 0.0);

    for (int d = 0; d < maxDepth; d++)
    {               
        Intersection firstPlanetIntersected = firstIntersection(ray);

        if (firstPlanetIntersected.t <= 0.0)
		{
            outColor += worldAmbient;
            break;
        }

        Planet hitPlanet = planets[firstPlanetIntersected.planetIndex];
        Material hitMaterial = materials[hitPlanet.materialIndex];

        outColor += hitMaterial.ambient * worldAmbient;
                    
        vec3 intersectionPoint = ray.startPos + firstPlanetIntersected.t * ray.direction;
        vec3 hitNormal = normalize(intersectionPoint - hitPlanet.position);

        outColor += calculateLighting(ray, hitPlanet, hitMaterial, intersectionPoint, hitNormal) * (maxDepth - d) / maxDepth;
                   
        ray.startPos = intersectionPoint + epsilon * hitNormal;
        ray.direction = reflect(ray.direction, hitNormal);
    }

	return outColor;
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);
   
    Ray ray;
    ray.startPos = camera.position;
    
    float alpha = tan(camera.fov / 2.0) * (FragPos.x - (camera.width / 2.0)) / (camera.width / 2.0);
    float beta = tan(camera.fov / 2.0) * ((camera.height / 2.0) - FragPos.y) / (camera.height / 2.0);
    ray.direction = normalize(camera.frontAxis + alpha * camera.sideAxis + beta * camera.upAxis);

    vec3 result = vec3(ray.direction); // trace(ray);

    FragColor = vec4(result, 1.0);
}