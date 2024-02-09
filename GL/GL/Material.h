#pragma once
#include <glm.hpp>
#include <glew.h>
#include <stb_image.h>

#include "Rendering/Shader.h"

class Material
{
public:
    // Always Base colour  -->  Normal
    Material(Shader& _shader, const std::string matPath[]);
    ~Material(){ glDeleteTextures(1, &colour_texture); };

    void BindTextures(GLuint texIndex) const;
    void UnbindTextures() const { glCall(glBindTexture(GL_TEXTURE_2D, 0)); }

    void SetUvScale(const glm::vec2& scale) { uvScale = scale; } 
    void SetUvScale(const float x, const float y) { uvScale = {x, y}; } 
    
    void EnableTextureWrapping() const
    {
        BindTextures(0);
        BindTextures(1);
        
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

        UnbindTextures();
    }

private:
    int tex_width, tex_height, channelCount;

    float specular = .2f;

    glm::vec2 uvScale = {1,1};
    
    GLuint colour_texture;
    GLuint normal_texture;

    Shader& shader;
};
