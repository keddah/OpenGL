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

    void SetFontSize(const short newSize) { fontSize = newSize; }
    glm::vec2 GetDrawSize() const { return drawSize; }
    
    void SetDrawPosition(const glm::vec2& pos) { drawPos = pos; }
    void SetDrawPosition(const float x, const float y) { drawPos = {x,y}; }
    glm::vec2 GetDrawPosition() const { return drawPos; }

    // Toggles if a value isn't given
    void SetVisible() { visible = !visible; }
    void SetVisible(const bool newVal) { visible = newVal; }
    
private:
    void Init();
    void GlRender() const;

    bool visible = true;
    
    GLuint vertArrayIndex;
    
    std::string text;
    std::string fontPath;
    unsigned short fontSize = 12;
    SDL_Color drawColour { 255, 255,255,255 };

    Shader shader {"Rendering/Shaders/UiVertShader.glsl", "Rendering/Shaders/UiFragShader.glsl"};

    glm::vec2 drawPos;
    glm::vec2 drawSize;

    glm::vec2 screenSize;
    
    GLuint texture = 0;

};
