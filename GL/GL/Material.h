#pragma once
#include <glm.hpp>
#include <glew.h>
#include <stb_image.h>

#include "Rendering/Shader.h"

class Material
{
public:
    Material(Shader& _shader, const std::string& matPath);
    ~Material(){ glDeleteTextures(1, &colour_texture); };

    void NewTexture(const std::string& filePath);
    void BindTexture() const { glCall(glBindTexture(GL_TEXTURE_2D, colour_texture)); }
    void UnbindTexture() const { glCall(glBindTexture(GL_TEXTURE_2D, 0)); }
    

private:
    int tex_width, tex_height, channelCount;
    unsigned char* image_bytes;
    
    glm::vec4 tint = {1,1,1,1};
    GLuint colour_texture;

    Shader& shader;
};
