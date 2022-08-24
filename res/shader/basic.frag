#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

const int MAX_POINT_LIGHTS = 10;

struct Light
{
	vec3 color;
};
struct AmbientLight
{
	Light base;
	float ambientIntensity;
};
struct DiffuseLight
{
	AmbientLight ambient;
	vec3 direction;
	float diffuseIntensity;
};
struct DirectionalLight
{
	DiffuseLight diffuse;
    vec3 direction;
};
struct PointLight
{
	DiffuseLight diffuse;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct Material
{
    float specularIntensity;
    float shininess;
};

uniform int pointLightCount;	
uniform sampler2D aTexture;
uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform Material material;
uniform vec3 eyePosition;

out vec4 FragColor;

vec4 CalcLightByDirection(DiffuseLight diffuse, vec3 direction)
{
	vec4 ambientColor = vec4(diffuse.ambient.base.color, 1.0f) * diffuse.ambient.ambientIntensity;
    float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
    vec4 diffuseColor = vec4(diffuse.ambient.base.color, 1.0f) * diffuse.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0, 0, 0, 0);

    if(diffuseFactor > 0.0f)
    {
        vec3 fragToEye = normalize(eyePosition - FragPos);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
        float specularFactor = dot(fragToEye, reflectedVertex);
        if(specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(diffuse.ambient.base.color * material.specularIntensity * specularFactor, 1.0f);
        }
    }
	
	return (ambientColor + diffuseColor + specularColor);
}

vec4 CalcDirectionalLight()
{
	return CalcLightByDirection(directionalLight.diffuse, directionalLight.direction);
}

vec4 CalcPointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);
	for(int i=0; i < pointLightCount; i++)
	{
		vec3 direction = FragPos - pointLights[i].position;
		float distance = length(direction);
		
		vec4 color = CalcLightByDirection(pointLights[i].diffuse, direction);
		float attenuation = pointLights[i].exponent * distance * distance + pointLights[i].linear * distance + pointLights[i].constant;
		totalColor += (color / attenuation);
	}
	return totalColor;
}

void main()
{
	vec4 finalColor = CalcDirectionalLight();
	finalColor += CalcPointLights();
	
	FragColor = texture(aTexture, TexCoord) * finalColor;
}

/*
void main()
{
    vec4 ambientColor = vec4(directionalLight.diffuse.ambient.base.color, 1.0f) * directionalLight.diffuse.ambient.ambientIntensity;
    float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
    vec4 diffuseColor = vec4(directionalLight.diffuse.ambient.base.color, 1.0f) * directionalLight.diffuse.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0, 0, 0, 0);

    if(diffuseFactor > 0.0f)
    {
        vec3 fragToEye = normalize(eyePosition - FragPos);
        vec3 reflectedVertex = normalize(reflect(directionalLight.direction, normalize(Normal)));
        float specularFactor = dot(fragToEye, reflectedVertex);
        if(specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(directionalLight.diffuse.ambient.base.color * material.specularIntensity * specularFactor, 1.0f);
        }
    }

    FragColor = texture(aTexture, TexCoord) * (ambientColor + diffuseColor + specularColor);
}
*/