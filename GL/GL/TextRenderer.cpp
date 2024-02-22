/**************************************************************************************************************
* Text Renderer - Code
*
* Creates a plane and a texture based on text input. Renders the text input to the plane and displays it at a specified position
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "TextRenderer.h"

#include <ext/matrix_clip_space.hpp>

void TextRenderer::Init()
{
    shader.Init();
    shader.Activate();

    vertArrayIndex = shader.GetAttribute("vertPos");

    shader.Deactivate();


    // Creating the text surface to get the size of the image (done so that the placement of the ui is easier to do)
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    
    if(!font)
    {
        print("bad filePath - text")
        return;
    }

    SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), drawColour);
    SDL_Surface* convertedImg = SDL_ConvertSurfaceFormat(textImage, SDL_PIXELFORMAT_RGBA32, 0);
    if(!textImage)
    {
        print("Unable to load surface image")
        return;
    }
    if (!convertedImg)
    {
        print("Unable to convert surface image")
        return;
    }

    drawSize = glm::vec2(convertedImg->w, convertedImg->h);

    // Cleanup
    TTF_CloseFont(font);
    SDL_FreeSurface(textImage);
    SDL_FreeSurface(convertedImg);
}

void TextRenderer::Draw(const std::string& toDisplay)
{
    if(!visible) return;
    
    text = toDisplay;

    // A new texture needs to be made every time the text needs to change...
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    
    if(!font)
    {
        print("bad filePath - text")
        return;
    }

    SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), drawColour);
    SDL_Surface* convertedImg = SDL_ConvertSurfaceFormat(textImage, SDL_PIXELFORMAT_RGBA32, 0);
    if(!textImage)
    {
        print("Unable to convert surface image")
        return;
    }

    if (!convertedImg)
    {
        print("Unable to convert surface image")
        return;
    }
    TTF_CloseFont(font);
    
    drawSize = glm::vec2(convertedImg->w, convertedImg->h);
    
    if(SDL_MUSTLOCK(convertedImg)) SDL_LockSurface(convertedImg);
    
    // Delete the old textures before creating new ones
    glCall(glDeleteTextures(1, &texture));

    // Creating the texture
    glCall(glGenTextures(1, &texture));
    glCall(glBindTexture(GL_TEXTURE_2D, texture));
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, drawSize.x, drawSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, convertedImg->pixels));
    
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    SDL_FreeSurface(textImage);
    SDL_FreeSurface(convertedImg);

    // Render the texture to screen
    GlRender();
}


void TextRenderer::GlRender() const
{
    GLuint vboTextQuad, vertArray;

    // Create a plane to display the texture
    const Vertex verts[] =
    {
        {{drawPos.x, drawPos.y, 0.0f}, {0,0,0},{0.0f, 1.0f}},
        {{drawPos.x, drawPos.y + drawSize.y, 0.0f}, {0,0,0},{0.0f, 0.0f}},
        {{drawPos.x + drawSize.x, drawPos.y + drawSize.y, 0.0f}, {0,0,0},{1.0f, 0.0f}},
        
        {{drawPos.x + drawSize.x, drawPos.y + drawSize.y, 0.0f}, {0,0,0},{1.0f, 0.0f}},
        {{drawPos.x + drawSize.x, drawPos.y, 0.0f}, {0,0,0},{1.0f, 1.0f}},
        {{drawPos.x, drawPos.y, 0.0f}, {0,0,0},{0.0f, 1.0f}}
    };

    // Create and bind vArray
    glCall(glGenVertexArrays(1, &vertArray));
    glCall(glBindVertexArray(vertArray));

    // Create and bind buffer
    glCall(glGenBuffers(1, &vboTextQuad));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vboTextQuad));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));

    shader.Activate();

    const glm::mat4 projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f);
    shader.SetMat4Attrib("projection", projection);

    glCall(glBindBuffer(GL_ARRAY_BUFFER, vboTextQuad));

    // Enable and set the vertex position attrib    
    glCall(glEnableVertexAttribArray(vertArrayIndex));
    glCall(glVertexAttribPointer(vertArrayIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position))));

    // Enabling and setting the UV attrib
    glCall(glEnableVertexAttribArray(1));
    glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)));

    glCall(glActiveTexture(GL_TEXTURE0));
    shader.SetIntAttrib("sampler", 0);
    glCall(glBindTexture(GL_TEXTURE_2D, texture));

    glCall(glEnable(GL_BLEND))
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    // Draw...
    glCall(glDrawArrays(GL_TRIANGLES, 0, 6));

    // Unbind the texture
    glCall(glBindTexture(GL_TEXTURE_2D, 0));

    // Disable the vertex position attrib
    glCall(glDisableVertexAttribArray(vertArrayIndex));

    // Disable the UV attrib
    glCall(glDisableVertexAttribArray(1));

    // Unbind the vArray
    glCall(glBindVertexArray(0));

    glCall(glDisable(GL_BLEND));
    
    shader.Deactivate();

    // Delete the buffer and vArray
    glCall(glDeleteBuffers(1, &vboTextQuad));
    glCall(glDeleteVertexArrays(1, &vertArray));
}
