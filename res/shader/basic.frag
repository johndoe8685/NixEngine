#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 LightSpacePos;

const int MAX_POINT_LIGHTS = 10;
const int MAX_SPOT_LIGHTS = 5;

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
	bool inUse;
};
struct SpotLight
{
    PointLight point;
    vec3 direction;
    float edge;
};
struct Material
{
    float specularIntensity;
    float shininess;
};

uniform sampler2D aTexture;
uniform sampler2D shadowMap;

uniform int pointLightCount;	
uniform int spotLightCount;

uniform float ShadowMapBiasMin;
uniform float ShadowMapBiasMax;

uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform Material material;
uniform vec3 eyePosition;



out vec4 FragColor;

float ShadowCalculation(vec4 LightSpacePos, vec3 direction)
{
	vec3 projCoords = LightSpacePos.xyz / LightSpacePos.w;
	projCoords = projCoords * 0.5 + 0.5; 
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float bias = max(ShadowMapBiasMax * (1.0 - dot(Normal, direction)), ShadowMapBiasMin);
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
		   float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
	       shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
	    }    
	}
	shadow /= 9.0;
    return shadow;
}

vec4 CalcLightByDirection(DiffuseLight diffuse, vec3 direction, float shadowFactor)
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
	
	return (ambientColor + (1.0 - shadowFactor) * (diffuseColor + specularColor));
}

vec4 CalcDirectionalLight()
{
	float shadow = ShadowCalculation(LightSpacePos, directionalLight.direction);
	return CalcLightByDirection(directionalLight.diffuse, directionalLight.direction, shadow);
}

vec4 CalcPointLight(PointLight point)
{
    vec3 direction = FragPos - point.position;
    float distance = length(direction);
    direction = normalize(direction);

    vec4 color = CalcLightByDirection(point.diffuse, direction, 0.0f);
    float attenuation = point.exponent * distance * distance + point.linear * distance + point.constant;

    return ( color / attenuation);
}

vec4 CalcSpotLight(SpotLight spot)
{
    vec3 rayDirection = normalize(FragPos - spot.point.position);
    float slFactor = dot(rayDirection, spot.direction);

    if(slFactor > spot.edge)
    {
        vec4 color = CalcPointLight(spot.point);
        return color * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - spot.edge)));
    }
    else
    {
        return vec4(0, 0, 0, 0);
    }
}

vec4 CalcPointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);
	for(int i=0; i < pointLightCount; i++)
	{
		if(pointLights[i].inUse)
		{
		vec3 direction = FragPos - pointLights[i].position;
		float distance = length(direction);
		
		vec4 color = CalcLightByDirection(pointLights[i].diffuse, direction, 0.0f);
		float attenuation = pointLights[i].exponent * distance * distance + pointLights[i].linear * distance + pointLights[i].constant;
		totalColor += (color / attenuation);
		}
	}
	return totalColor;
}
vec4 CalcSpotLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);
	for(int i = 0; i < spotLightCount; i++)
	{		
		totalColor += CalcSpotLight(spotLights[i]);
	}
	
	return totalColor;
}

void main()
{
	vec4 finalColor = CalcDirectionalLight();
	finalColor += CalcPointLights();
    finalColor += CalcSpotLights();
	
	FragColor = texture(aTexture, TexCoord) * finalColor;
}