/**************************************************************************************************************
* Fragment Shader - Shader
*
* The shader code responsible for rendering the colour of objects.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#version 330 core

//in vec4 colour;
in vec2 texCoords;
in vec3 normals;
in vec3 fragPosition;

// Base colour
uniform sampler2D tex0;

// Normal Map
uniform sampler2D tex1;
uniform int normalPresent;

uniform vec2 uvScale;
uniform float specularStrength;

uniform float intensity;
uniform vec3 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;


int texSize;

out vec4 fragmentColour;
void main() 
{ 
    vec2 scaledTexure = texCoords * uvScale;
    
    // The normal map (from a texture)
    vec3 normalMapping = texture(tex1, scaledTexure).rgb;
    normalMapping = normalize(normalMapping * 2 - 1);
    
    texSize = textureSize(tex1, 0).x;
    
    // Normal from the vertex data
    vec3 vertexNormal = normalize(normals);             
    
    // If a normal map hasn't been assigned... use the normals from the vertex data
    vec3 normal = normalPresent == 1? normalMapping : vertexNormal;
    
    vec3 ambient = intensity * lightColour;
    
    vec3 lightDirection = normalize(lightPos - fragPosition);
    float diff = max(dot(normal, lightDirection), 0);
    vec3 diffusion = diff * lightColour;

    vec3 viewDirection = normalize(camPos - fragPosition);
    vec3 reflection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflection), 0), 32);
    vec3 specular = lightColour * specularStrength * spec;

    vec3 texColour = texture(tex0, scaledTexure).rgb;
    
    // Commented part for debugging (things that have a normal map will be white... things that don't will be normal).
    vec3 output = ((ambient + diffusion) * texColour + specular);// * (normalPresent == 1 ? 1000000.0f : 1.0f);

    fragmentColour = vec4(output, 1); 
}

