/**************************************************************************************************************
* Image Renderer - Header
*
* Defines transformation functions and instantiates a shader that's specific to creating UI.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#pragma once

#include <SDL_pixels.h>

#include "Rendering/BufferArrayManager.h"
#include "Rendering/Shader.h"


class ImageRenderer
{
public:
    ImageRenderer(std::string _filePath, const glm::vec2& screensize) : screenSize(screensize), filePath(std::move(_filePath)) { Init(); }
    ~ImageRenderer() { glCall(glDeleteTextures(1, &texture)); }
    
    void Draw() const;
    
    glm::vec2 GetDrawSize() const { return drawSize; }
    void SetDrawSize(const glm::vec2& _size) { drawSize = _size; }
    
    void SetDrawSize(const float x, const float y) { drawSize = {x, y}; }
    
    void SetDrawPosition(const glm::vec2& pos) { drawPos = pos; }
    void SetDrawPosition(const float x, const float y) { drawPos = {x,y}; }

    // Toggles if a value isn't given
    void SetVisible() { visible = !visible; }
    void SetVisible(const bool newVal) { visible = newVal; }
    
private:
    void Init();
    void CreateTexture();

    bool visible = true;
    
    GLuint vertArrayIndex;
    
    std::string filePath;

    Shader shader {"Rendering/Shaders/UiVertShader.glsl", "Rendering/Shaders/UiFragShader.glsl"};

    glm::vec2 drawPos;
    glm::vec2 drawSize;

    glm::vec2 screenSize;
    
    GLuint texture;
};
