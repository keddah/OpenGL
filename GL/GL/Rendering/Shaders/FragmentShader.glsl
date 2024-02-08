#version 330 core

//in vec4 colour;
in vec2 texCoords;
in vec3 normals;
in vec3 fragPosition;

// Base colour
uniform sampler2D tex0;

// Normal Map
uniform sampler2D tex1;

uniform float intensity;
uniform vec3 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;

out vec4 fragmentColour;
void main() 
{ 
    // The normal map (from a texture)
    vec3 normalMapping = texture(tex1, texCoords).rgb;
    normalMapping = normalize(normalMapping * 2 - 1);
    
    // Normal from the vertex data
    vec3 vertexNormal = normalize(normals);             
    
    // If a normal map hasn't been assigned... use the normals from the vertex data
    vec3 normal = all(equal(normalMapping, vec3(0.0))) ? vertexNormal : normalMapping;
    
    vec3 ambient = intensity * lightColour;
    
    vec3 lightDirection = normalize(lightPos - fragPosition);
    float diff = max(dot(normal, lightDirection), 0);
    vec3 diffusion = diff * lightColour;

    float specularStrength = .2f;
    vec3 viewDirection = normalize(camPos - fragPosition);
    vec3 reflection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflection), 0), 32);
    vec3 specular = lightColour * specularStrength * spec;

    vec3 texColour = texture(tex0, texCoords).rgb;

    vec3 output = (ambient + diffusion) * texColour + specular;

    fragmentColour = vec4(output, 1); 
}

