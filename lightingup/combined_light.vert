#version 330 core

precision mediump float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    Normal = mat3(transpose(inverse(view * model))) * normal;
    FragPos = vec3 (view * model * vec4(position, 1.0));
    TexCoords = texCoords;
}