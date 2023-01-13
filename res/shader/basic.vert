#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 norm;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;

out vec2 TexCoord;
out vec3 color;
out vec3 Normal;
out vec3 FragPos;
out vec4 LightSpacePos;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    LightSpacePos = lightSpaceMatrix * model * vec4(pos, 1.0);
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * norm;
    FragPos = (model * vec4(pos, 1.0)).xyz;
}