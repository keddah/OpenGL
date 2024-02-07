#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTex;

//out vec4 colour;
out vec3 normals;
out vec2 texCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() 
{ 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1); 
    //colour = vColour;
    normals = vec3(0,0,0); //vec3(modelMatrix ? vec4(vNormal, 1.0f));
    texCoords = vTex;
}
