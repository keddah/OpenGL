#version 330 core

//in vec4 colour;
in vec2 texCoords;
in vec3 normals;

uniform sampler2D tex0;
// uniform vec3 lightColour;
// uniform vec3 lightPos;
// uniform vec3 camPos;

out vec4 fragmentColour;
void main() 
{ 
    fragmentColour = texture(tex0, texCoords);// * colour; 
}

