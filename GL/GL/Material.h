#pragma once
#include <glm.hpp>
#include <glew.h>
#include <stb_image.h>
#include <vector>

#include "Rendering/Shader.h"

class Material
{
public:
    // Always Base colour  -->  Normal
    Material(Shader& _shader, const std::vector<std::string>& matPath);
    ~Material(){ glCall(glDeleteTextures(1, &colour_texture)); glCall(glDeleteTextures(1, &normal_texture)); };

    void BindTextures(GLint texIndex) const;
    void UnbindTextures() const { glCall(glBindTexture(GL_TEXTURE_2D, 0)); }

    void SetUvScale(const glm::vec2& scale) { uvScale = scale; } 
    void SetUvScale(const float x, const float y) { uvScale = {x, y}; } 
    
    void SetSpecular(const float spec) { specular = spec; }
    
private:
    int tex_width, tex_height, channelCount;

    const std::vector<std::string>& texturePaths;
    
    float specular = .2f;

    glm::vec2 uvScale = {1,1};
    
    GLuint colour_texture;
    GLuint normal_texture;

    Shader& shader;
};
