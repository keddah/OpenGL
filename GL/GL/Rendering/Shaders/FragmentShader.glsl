#version 330 core

uniform vec4 fragColour;
out vec4 fragmentColor;

void main() 
{ 
    fragmentColor = fragColour;
}

