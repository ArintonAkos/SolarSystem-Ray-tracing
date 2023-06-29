#version 460 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float shininess;
};

struct Hit {
		float t;
		vec3 position, normal;
		int mat;
        int planetIndex;
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
    int depth;
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

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse;

// uniform Light light;
uniform Camera camera; 

uniform Planet planets[15];
uniform int planetCount;  

uniform Light lights[4];
uniform int lightCount;

uniform Material materials[15];
uniform int materialCount;

uniform int maxDepth = 10;
uniform vec3 worldAmbient;

Hit intersect (Ray ray, int planetIndex)
{
    Planet planet = planets[planetIndex];
    Hit hit;
	hit.t = -1;

	vec3 dist = ray.startPos - planet.position;

	float a = dot(ray.direction, ray.direction);
	float b = dot(dist, ray.direction) * 2.0f;
	float c = dot(dist, dist) - planet.radius * planet.radius;
	float discr = b * b - 4.0f * a * c;
	if (discr < 0) return hit;

	float sqrt_discr = sqrt(discr);
	float t1 = (-b + sqrt_discr) / 2.0f / a;	// t1 >= t2 for sure
	float t2 = (-b - sqrt_discr) / 2.0f / a;
	if (t1 <= 0) return hit;
	hit.t = (t2 > 0) ? t2 : t1;

	hit.position = ray.startPos + ray.direction * hit.t;
	hit.normal = (hit.position - planet.position) / planet.radius;
	hit.planetIndex = planetIndex;

	return hit;
}

Hit firstIntersection(Ray ray) 
{
    Hit bestHit;
	bestHit.t = -1;

	for (int i = 0; i < planetCount; i++) {
		Hit hit = intersect(ray, i);

		if (hit.t > 0 && (bestHit.t < 0 || hit.t < bestHit.t))  
            bestHit = hit;
	}

	if (dot(ray.direction, bestHit.normal) > 0) 
        bestHit.normal = bestHit.normal * (-1);
	
    return bestHit;
}

bool shadowIntersect(Ray ray) {	
	for (int i = 0; i < planetCount; i++) 
        if (intersect(ray, i).t > 0) return true; 

	return false;
}

vec3 calculateLighting(Ray ray, Hit hit)
{
    float epsilon = 0.0001;
    vec3 outColor = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < lightCount; i++) 
	{
        Ray shadowRay;
        shadowRay.startPos = hit.position + epsilon * hit.normal;
        shadowRay.direction = normalize(lights[i].position - hit.position);
                        
        float cosTheta = dot(hit.normal, shadowRay.direction);

        if (cosTheta > 0.0)
	    {
            int materialIndex = planets[hit.planetIndex].materialIndex;
			outColor += materials[materialIndex].ambient * lights[i].ambient * cosTheta;
            vec3 halfway = normalize(shadowRay.direction - ray.direction);

            float cosDelta = dot(hit.normal, halfway);
            if (cosDelta > 0)
				outColor += materials[materialIndex].specular * lights[i].specular * pow(cosDelta, materials[materialIndex].shininess);
	    }
    }

    return outColor;
}

vec3 trace (Ray ray)
{
    const float epsilon = 0.1;
    vec3 outColor = vec3(0.0, 0.0, 0.0);

    for (int d = 0; d < maxDepth; d++)
    {               
        //if (ray.depth >= maxDepth) 
          //  break;

        Hit hit = firstIntersection(ray);

        if (hit.t <= 0.0)
		{
            outColor += worldAmbient;
            break;
        }

        Planet hitPlanet = planets[hit.planetIndex];
        Material hitMaterial = materials[hitPlanet.materialIndex];

        outColor += hitMaterial.ambient * worldAmbient;
        outColor += calculateLighting(ray, hit);
                   
        ray.startPos = hit.position + epsilon * hit.normal;
        ray.direction = reflect(ray.direction, hit.normal);
    }

	return outColor;
}

void main()
{ 
    Ray ray;
    ray.startPos = camera.position;
    
    float aspect = camera.width / camera.height;
    float alpha = tan(camera.fov / 2.0) * (gl_FragCoord.x - (camera.width / 2.0)) / (camera.width / 2.0);
    float beta = tan(camera.fov / 2.0) * ((camera.height / 2.0) - gl_FragCoord.y) / (camera.height / 2.0) / aspect;
    ray.direction = normalize(camera.frontAxis + alpha * camera.sideAxis - beta * camera.upAxis);

    vec3 result = trace(ray);

    FragColor = vec4(result, 1.0);
}