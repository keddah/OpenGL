/**************************************************************************************************************
* Material - Header
*
* Creates a shader that can be bound to a mesh. The mesh that creates an instance of this class will be able to assign textures and set the UV scale.
* The shader is used to bind materials/textures to the mesh using the BindTextures function.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


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
    Material(const std::vector<std::string>& matPath);
    ~Material(){ glCall(glDeleteTextures(1, &colour_texture)); glCall(glDeleteTextures(1, &normal_texture)); };

    void BindTextures(GLint texIndex) const;
    void UnbindTextures() const { glCall(glBindTexture(GL_TEXTURE_2D, 0)); }

    void SetUvScale(const glm::vec2& scale) { uvScale = scale; } 
    void SetUvScale(const float x, const float y) { uvScale = {x, y}; } 
    
    void SetSpecular(const float spec) { specular = spec; }

    Shader& GetShader() { return shader; }
    
private:
    int tex_width, tex_height, channelCount;

    const std::vector<std::string>& texturePaths;
    
    float specular = .2f;

    glm::vec2 uvScale = {1,1};
    
    GLuint colour_texture;
    GLuint normal_texture;

    Shader shader {"Rendering/Shaders/VertexShader.glsl", "Rendering/Shaders/FragmentShader.glsl"};
};
