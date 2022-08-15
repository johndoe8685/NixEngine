#version 330 core

in vec2 TexCoord;
in vec3 Normal;

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;

    vec3 direction;
    float diffuseIntensity;
};

uniform sampler2D aTexture;
uniform DirectionalLight directionalLight;

out vec4 FragColor;

void main()
{
    vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;
    float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
    vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
    FragColor = texture(aTexture, TexCoord) * (ambientColor + diffuseColor);
}