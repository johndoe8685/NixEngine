#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec2 TexCoord;
out vec3 color;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    TexCoord = aTexCoord;
}