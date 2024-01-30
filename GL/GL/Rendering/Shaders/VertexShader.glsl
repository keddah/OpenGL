#version 330 core

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in vec4 vColour;

out vec4 colour;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() 
{ 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertexPos; 
    colour = vColour;
}
