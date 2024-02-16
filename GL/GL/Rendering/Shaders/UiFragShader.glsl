#version 330 core

in vec2 uv;
uniform sampler2D sampler;

out vec4 fragColour;


void main()
{
    vec4 texColour = texture(sampler, uv);
    
    fragColour = texColour;
}
