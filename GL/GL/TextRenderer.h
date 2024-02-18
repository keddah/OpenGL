#pragma once

#include <string>
#include <vector>

#include <SDL_ttf.h>

#include "Rendering/BufferArrayManager.h"
#include "Rendering/Shader.h"

class TextRenderer
{
public:
    TextRenderer(std::string toDisplay, std::string _fontPath, const short size) : text(std::move(toDisplay)), fontPath(std::move(_fontPath)), fontSize(size) { Init(); SetFontSize(size); }

    void Draw(const std::string& toDisplay);
    
    void SetScreenSize(const glm::vec2& _size) { screenSize = _size; }

    void SetDrawColour(const SDL_Color& colour) { drawColour = colour; }
    void SetDrawColour(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) { drawColour = SDL_Color{r,g,b,a}; }

    void SetFontSize(short newSize);
    glm::vec2 GetSize() const { return size; }
    
    void SetDrawPosition(const glm::vec2& pos) { drawPos = pos; }
    void SetDrawPosition(const float x, const float y) { drawPos = {x,y}; }
    
private:
    void Init();
    void GlRender() const;
    
    GLuint vertArrayIndex;
    
    std::string text;
    std::string fontPath;
    unsigned short fontSize = 12;
    SDL_Color drawColour { 255, 255,255,255 };

    Shader shader {"Rendering/Shaders/UiVertShader.glsl", "Rendering/Shaders/UiFragShader.glsl"};

    glm::vec2 drawPos;
    glm::vec2 size;

    glm::vec2 screenSize;
    
    GLuint texture;

};
