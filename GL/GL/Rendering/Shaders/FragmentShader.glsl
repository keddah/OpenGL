#version 330 core

uniform vec4 colour;
out vec4 fragmentColor;

void main() 
{ 
    fragmentColor = vec4(colour); 
}

