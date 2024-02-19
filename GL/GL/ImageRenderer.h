#pragma once

#include <iostream>
#include <SDL_pixels.h>

#include "Rendering/BufferArrayManager.h"
#include "Rendering/Shader.h"


class ImageRenderer
{
public:
    ImageRenderer(std::string _filePath) : filePath(std::move(_filePath)) { Init(); }
    
    void Draw() const;
    
    void SetScreenSize(const glm::vec2& _size) { screenSize = _size; }

    glm::vec2 GetDrawSize() const { return drawSize; }
    void SetDrawSize(const glm::vec2& _size)
    {
        if(_size == drawSize) return;

        drawSize = _size;
        CreateTexture();
    }
    
    void SetDrawSize(const float x, const float y)
    {
        if(glm::vec2(x,y) == drawSize) return;

        drawSize = {x, y};
        CreateTexture();
    }
    

    
    void SetDrawPosition(const glm::vec2& pos) { drawPos = pos; }
    void SetDrawPosition(const float x, const float y) { drawPos = {x,y}; }
    
private:
    void Init();

    void CreateTexture();
    
    GLuint vertArrayIndex;
    
    std::string filePath;
    unsigned short fontSize = 12;

    Shader shader {"Rendering/Shaders/UiVertShader.glsl", "Rendering/Shaders/UiFragShader.glsl"};

    glm::vec2 drawPos;
    glm::vec2 drawSize;

    glm::vec2 screenSize;
    
    GLuint texture;
};
