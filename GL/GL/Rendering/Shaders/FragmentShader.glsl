#version 330 core

uniform vec3 colour;
out vec4 fragmentColor;

void main() 
{ 
    fragmentColor = vec4(colour.xyz, 1.0); 
}

