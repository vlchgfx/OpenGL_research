#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vsTexCoord;

out vec2 fsTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    //gl_Position = model * vec4(position, 1.0);
    fsTexCoord = vec2(vsTexCoord.x, 1.0 - vsTexCoord.y);
}