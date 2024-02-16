#version 330 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 texCoords;

out vec2 uv;

uniform mat4 projection;


void main()
{
    vec4 outpos = projection * vec4(vertPos.xyz, 1);
    gl_Position = outpos;
    
    uv = texCoords;
}
