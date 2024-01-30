#pragma once
#include <glm.hpp>
#include <glew.h>
#include <stb_image.h>

#include "Rendering/Shader.h"

class Material
{
public:
    Material(Shader& _shader);
    ~Material(){ glDeleteTextures(1, &colour_texture); };

    void NewTexture(std::string filePath);
    void BindTexture() const { glBindTexture(GL_TEXTURE_2D, colour_texture); }
    void UnbindTexture() const { glBindTexture(GL_TEXTURE_2D, 0); }
    
    void SetTint(glm::vec4 colour);

private:
    int tex_width, tex_height, channelCount;
    unsigned char* image_bytes;
    
    glm::vec4 tint = {1,1,1,1};
    GLuint colour_texture;

    Shader& shader;
};
