#include "TextRenderer.h"

#include <ext/matrix_clip_space.hpp>

void TextRenderer::Draw(const std::string& toDisplay)
{
    text = toDisplay;
    
    TTF_Font* font = TTF_OpenFont("Fonts/Quicksand-Regular.ttf", fontSize);
    
    if(!font)
    {
        print("bad filePath - text")
        return;
    }
    
    // The following creates an image representing the text that we input
    SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), {255,255,255,255});
    SDL_Surface* convertedImg = SDL_ConvertSurfaceFormat(textImage, SDL_PIXELFORMAT_RGBA32, 0);
    TTF_CloseFont(font);
    
    if(!convertedImg)
    {
        print("Unable to convert surface image")
        return;
    }
    
    textImage = convertedImg;
    
    size = {textImage->w, textImage->h};
    
    if(SDL_MUSTLOCK(textImage)) SDL_LockSurface(textImage);
    
    const int bytesPerRow = size.x * textImage->format->BytesPerPixel;
    char* temp = new char[bytesPerRow];
    
    for(int i = 0; i < size.y / 2; i++)
    {
        memcpy(temp, ((char*)textImage->pixels) + ((static_cast<int>(size.y) - i - 1) * bytesPerRow), bytesPerRow);
        memcpy(((char*)textImage->pixels) + ((static_cast<int>(size.y) - i - 1) * bytesPerRow), (char*)textImage->pixels + (i * bytesPerRow), bytesPerRow);
        memcpy((char*)textImage->pixels + (i * bytesPerRow), temp, bytesPerRow);
    }
    delete[] temp;
    
    
    // Creating the texture
    glCall(glGenTextures(1, &texture));
    glCall(glBindTexture(GL_TEXTURE_2D, texture));
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textImage->pixels));
    
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    SDL_FreeSurface(textImage);


    GlRender();
}

// void TextRenderer::SetText(const std::string& toDisplay, const std::string& _fontPath)
// {
//     text = toDisplay;
//     fontPath = _fontPath;
//     
//     TTF_Font* font = TTF_OpenFont(_fontPath.c_str(), fontSize);
//
//     if(!font)
//     {
//         print("bad filePath - text")
//         return;
//     }
//
//     // The following creates an image representing the text that we input
//     SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), {255,255,255,255});
//     SDL_Surface* convertedImg = SDL_ConvertSurfaceFormat(textImage, SDL_PIXELFORMAT_RGBA32, 0);
//     TTF_CloseFont(font);
//
//     if(!convertedImg)
//     {
//         print("Unable to convert surface image")
//         return;
//     }
//
//     textImage = convertedImg;
//     
//     size = {textImage->w, textImage->h};
//
//     if(SDL_MUSTLOCK(textImage)) SDL_LockSurface(textImage);
//
//     const int bytesPerRow = size.x * textImage->format->BytesPerPixel;
//     char* temp = new char[bytesPerRow];
//
//     for(int i = 0; i < size.y * .5f; i++)
//     {
//         memcpy(temp, ((char*)textImage->pixels) + ((static_cast<int>(size.y) - i - 1) * bytesPerRow), bytesPerRow);
//         memcpy(((char*)textImage->pixels) + ((static_cast<int>(size.y) - i - 1) * bytesPerRow), (char*)textImage->pixels + (i * bytesPerRow), bytesPerRow);
//         memcpy((char*)textImage->pixels + (i * bytesPerRow), temp, bytesPerRow);
//     }
//
//     delete[] temp;
//
//
//     // Creating the texture
//     glCall(glGenTextures(1, &texture));
//     glCall(glBindTexture(GL_TEXTURE_2D, texture));
//     glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textImage->pixels));
//
//     glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//     glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//
//     SDL_FreeSurface(textImage);
// }

void TextRenderer::Init()
{
    // const GLfloat verts[] =
    // {
    //     drawPos.x, drawPos.y, 0.0f, 0.0f, 1.0f,
    //     drawPos.x, drawPos.y + size.y, 0.0f, 0.0f, 0.0f,
    //     drawPos.x + size.x, drawPos.y + size.y, 0.0f, 1.0f, 0.0f,
    //
    //     drawPos.x + size.x, drawPos.y + size.y, 0.0f, 1.0f, 0.0f,
    //     drawPos.x + size.x, drawPos.y, 0.0f, 1.0f, 1.0f,
    //     drawPos.x, drawPos.y, 0.0f, 0.0f, 1.0f
    // };
    //
    // glCall(glGenVertexArrays(1, &vertArray));
    // glCall(glBindVertexArray(vertArray));
    //
    // glCall(glGenBuffers(1, &vertBuffer));
    // glCall(glBindBuffer(GL_ARRAY_BUFFER, vertBuffer))
    // glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));

    shader.Init();
    shader.Activate();
    const glm::mat4 projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    shader.SetMat4Attrib("projection", projection);
    shader.Deactivate();

    vertArrayIndex = shader.GetAttribute("vertPos");

    if (vertArrayIndex == -1)
    {
        print("Couldn't get shader attribute - Vertex Position")
        print(glGetError())
        return;
    }
}

void TextRenderer::GlRender()
{
    GLuint vboTextQuad, vertArray;
    
    const Vertex verts[] =
    {
        {{drawPos.x, drawPos.y, 0.0f}, {0,0,0},{0.0f, 1.0f}},
        {{drawPos.x, drawPos.y + size.y, 0.0f}, {0,0,0},{0.0f, 0.0f}},
        {{drawPos.x + size.x, drawPos.y + size.y, 0.0f}, {0,0,0},{1.0f, 0.0f}},

        {{drawPos.x + size.x, drawPos.y + size.y, 0.0f}, {0,0,0},{1.0f, 0.0f}},
        {{drawPos.x + size.x, drawPos.y, 0.0f}, {0,0,0},{1.0f, 1.0f}},
        {{drawPos.x, drawPos.y, 0.0f}, {0,0,0},{0.0f, 1.0f}}
    };
    
    glCall(glGenVertexArrays(1, &vertArray));
    glCall(glBindVertexArray(vertArray));

    glCall(glGenBuffers(1, &vboTextQuad));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vboTextQuad));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));

    shader.Activate();

    const glm::mat4 projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    shader.SetMat4Attrib("projection", projection);

    glCall(glEnableVertexAttribArray(vertArrayIndex));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vboTextQuad));

    glCall(glVertexAttribPointer(vertArrayIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position))));

    
    glCall(glEnableVertexAttribArray(1));
    glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)));

    glCall(glActiveTexture(GL_TEXTURE0));
    shader.SetIntAttrib("sampler", 0);
    glCall(glBindTexture(GL_TEXTURE_2D, texture));

    glCall(glDrawArrays(GL_TRIANGLES, 0, 6));

    glCall(glBindTexture(GL_TEXTURE_2D, 0));
    glCall(glDisableVertexAttribArray(vertArrayIndex));
    glCall(glDisableVertexAttribArray(1));
    glCall(glBindVertexArray(0));

    shader.Deactivate();
    glCall(glDeleteBuffers(1, &vboTextQuad));
}
