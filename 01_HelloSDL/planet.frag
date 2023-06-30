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
    vec3 position;
    vec3 normal;
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

uniform Camera camera; 

uniform Planet planets[15];
uniform int planetCount;  

uniform Light lights[4];
uniform int lightCount;

uniform Material materials[15];
uniform int materialCount;

uniform int maxDepth;
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
	float t1 = (-b + sqrt_discr) / 2.0f / a;
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

bool inShadow(Hit hit, Ray shadowRay, Light light)
{
    Hit shadowHit = firstIntersection(shadowRay);
    if (shadowHit.t > 0)
    {
        float distToLight = length(light.position - hit.position);
        float distToShadowHit = length(shadowHit.position - hit.position);

        if (distToShadowHit < distToLight)
			return true;
    }

    return false;
}

vec3 calculateLighting(Ray ray, Hit hit)
{
    float epsilon = 0.0001;
    vec3 color = vec3(0.0);

    for (int i = 0; i < lightCount; i++)
    {
        Ray shadowRay;
        shadowRay.startPos = hit.position + epsilon * hit.normal;
        shadowRay.direction = normalize(lights[i].position - hit.position);

         int materialIndex = planets[hit.planetIndex].materialIndex;
         Material material = materials[materialIndex];

        if (inShadow(hit, shadowRay, lights[i]))
        {
            //color += material.ambient;
            continue;
        }
			

        float cosTheta = dot(hit.normal, shadowRay.direction);

        if (cosTheta > 0.0)
        {
           

            // Ambient component
            vec3 ambient = material.ambient * lights[i].ambient;

            // Diffuse component
            vec3 diffuse = material.diffuse * lights[i].diffuse * cosTheta;

            // Specular component
            vec3 halfway = normalize(shadowRay.direction - ray.direction);
            float cosDelta = dot(hit.normal, halfway);
            vec3 specular = material.specular * lights[i].specular * pow(cosDelta, material.shininess);

            color += ambient + diffuse + specular;
        }
    }

    return color;
}



vec3 trace (Ray ray)
{
    const float epsilon = 0.001;
    vec3 color = vec3(0.0, 0.0, 0.0);

    vec3 averageLightPosition = vec3(0.0);

    for (int i = 0; i < lightCount; i++)
    {
		    averageLightPosition += lights[i].position;
    }

    averageLightPosition /= lightCount;

    for (int d = 0; d < maxDepth; d++)
    {               
        Hit hit = firstIntersection(ray);

        if (hit.t <= 0.0)
		{
            color += worldAmbient;
            break;
        }

        if (d == 0)
        {
            float distance = length(camera.position - averageLightPosition);
            float distanceFactor = 1.0 / ( max (1.0, ( distance / 150 )));
            color += distanceFactor * calculateLighting(ray, hit);
        }
        
        //visszaverodes a bolygokrol
        
        ray.startPos = hit.position + epsilon * hit.normal;
        ray.direction = reflect(ray.direction, hit.normal);
    }

	return color;
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