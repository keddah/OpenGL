#pragma once

#include <string>
#include <vector>

#include <SDL_ttf.h>

#include "Rendering/BufferArrayManager.h"
#include "Rendering/Shader.h"

class TextRenderer
{
public:
    TextRenderer() { shader.Init(); }

    void Draw(const glm::mat4& projectionpro) const;
    void SetText(const std::string& toDisplay, const std::string& _fontPath);
    void SetFontSize(const short newSize) { fontSize = newSize; }

    void SetDrawPosition(const glm::vec2& pos) { drawPos = pos; }
    void SetDrawPosition(const float x, const float y) { drawPos = {x,y}; }
    
private:
    void CreateBufferManager();
    BufferArrayManager* baManager;
    
    std::string text;
    std::string fontPath;
    unsigned short fontSize = 12;
    glm::vec4 drawColour;

    GLuint vertPosAddress, uvAddress;
    Shader shader {"Rendering/Shaders/UiVertShader.glsl", "Rendering/Shaders/UiFragShader.glsl"};

    glm::vec2 drawPos;
    glm::vec2 size;
    
    GLuint texture;
};
