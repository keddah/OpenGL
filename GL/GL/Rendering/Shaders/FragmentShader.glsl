#version 330 core

//in vec4 colour;
in vec2 texCoords;
in vec3 normals;
in vec3 fragPosition;

uniform sampler2D tex0;

uniform float intensity;
uniform vec3 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;

out vec4 fragmentColour;
void main() 
{ 
    vec3 ambient = intensity * lightColour;

    vec3 vertexNormal = normalize(normals);
    vec3 lightDirection = normalize(lightPos - fragPosition);
    float diff = max(dot(vertexNormal, lightDirection), 0);
    vec3 diffusion = diff * lightColour;

    float specularStrength = .2f;
    vec3 viewDirection = normalize(camPos - fragPosition);
    vec3 reflection = reflect(-lightDirection, vertexNormal);
    float spec = pow(max(dot(viewDirection, reflection), 0), 32);
    vec3 specular = lightColour * specularStrength * spec;

    vec3 texColour = texture(tex0, texCoords).rgb;

    vec3 output = (ambient + diffusion) * texColour + specular;

    fragmentColour = vec4(output, 1); 
}

