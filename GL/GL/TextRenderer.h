#pragma once

#include <string>
#include <vector>

#include <SDL_ttf.h>

#include "Rendering/BufferArrayManager.h"
#include "Rendering/Shader.h"

class TextRenderer
{
public:
    TextRenderer() { Init(); }

    void Draw(const std::string& toDisplay);
    void SetText(const std::string& toDisplay, const std::string& _fontPath);
    void SetFontSize(const short newSize) { fontSize = newSize; }

    void SetDrawPosition(const glm::vec2& pos) { drawPos = pos; }
    void SetDrawPosition(const float x, const float y) { drawPos = {x,y}; }
    
private:
    void Init();
    void GlRender();
    
    GLuint vertArrayIndex;
    
    std::string text;
    std::string fontPath;
    unsigned short fontSize = 12;
    glm::vec4 drawColour;

    Shader shader {"Rendering/Shaders/UiVertShader.glsl", "Rendering/Shaders/UiFragShader.glsl"};

    glm::vec2 drawPos;
    glm::vec2 size;
    
    GLuint texture;

};
