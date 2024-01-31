#version 330 core

in vec4 colour;
in vec2 texCoords;

uniform sampler2D tex0;

out vec4 fragmentColour;
void main() 
{ 
    fragmentColour = texture(tex0, texCoords);// * vec4(colour, 1.0); 
}

