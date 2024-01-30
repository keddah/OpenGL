#version 330 core

in vec4 colour;
in vec2 texCoords;

uniform sampler2D tex0;

out vec4 fragmentColor;
void main() 
{ 
    fragmentColor = colour; //* texture(tex0, texCoords);
}

