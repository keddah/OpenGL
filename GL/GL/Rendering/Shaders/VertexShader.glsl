/**************************************************************************************************************
* Vertex Shader - Shader
*
* The shader code responsible for providing the data required for the placement of objects in the world
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTex;

//out vec4 colour;
out vec3 normals;
out vec2 texCoords;

out vec3 fragPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() 
{ 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1); 
    normals = vec3(modelMatrix * vec4(vNormal, 1.0f));
    texCoords = vTex;

    fragPosition = vec3(modelMatrix * vec4(vertexPos, 1.0f));
}
