#include "ImageRenderer.h"

#include <SDL_image.h>
#include <ext/matrix_clip_space.hpp>

#include "Rendering/BufferArrayManager.h"

void ImageRenderer::Init()
{
    shader.Init();
    shader.Activate();

    vertArrayIndex = shader.GetAttribute("vertPos");

    if (vertArrayIndex < 0)
    {
        print("Couldn't get shader attribute - Vertex Position")
        print(glGetError())
    }

    shader.Deactivate();

    CreateTexture();
}

void ImageRenderer::CreateTexture()
{
    glCall(glDeleteTextures(1, &texture));
    
    SDL_Surface* textImage = IMG_Load(filePath.c_str());

    // Don't assign the size if it's been resized
    drawSize = {textImage->w, textImage->h};
    
    // Creating the texture
    glCall(glGenTextures(1, &texture));
    glCall(glBindTexture(GL_TEXTURE_2D, texture));
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, drawSize.x, drawSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textImage->pixels));
    
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    SDL_FreeSurface(textImage);
}


void ImageRenderer::Draw() const
{
    if(!visible) return;
    
    GLuint vboTextQuad, vertArray;

    // The vertices for a plane
    const Vertex verts[] =
    {
        {{drawPos.x, drawPos.y, 0.0f}, {0,0,0},{0.0f, 1.0f}},
        {{drawPos.x, drawPos.y + drawSize.y, 0.0f}, {0,0,0},{0.0f, 0.0f}},
        {{drawPos.x + drawSize.x, drawPos.y + drawSize.y, 0.0f}, {0,0,0},{1.0f, 0.0f}},
        
        {{drawPos.x + drawSize.x, drawPos.y + drawSize.y, 0.0f}, {0,0,0},{1.0f, 0.0f}},
        {{drawPos.x + drawSize.x, drawPos.y, 0.0f}, {0,0,0},{1.0f, 1.0f}},
        {{drawPos.x, drawPos.y, 0.0f}, {0,0,0},{0.0f, 1.0f}}
    };
    
    glCall(glGenVertexArrays(1, &vertArray));
    glCall(glBindVertexArray(vertArray));

    glCall(glGenBuffers(1, &vboTextQuad));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vboTextQuad));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));

    shader.Activate();

    const glm::mat4 projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f);
    shader.SetMat4Attrib("projection", projection);

    glCall(glEnableVertexAttribArray(vertArrayIndex));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vboTextQuad));

    glCall(glVertexAttribPointer(vertArrayIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position))));

    
    glCall(glEnableVertexAttribArray(1));
    glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)));

    glCall(glActiveTexture(GL_TEXTURE0));
    shader.SetIntAttrib("sampler", 0);
    glCall(glBindTexture(GL_TEXTURE_2D, texture));

    glCall(glEnable(GL_BLEND))
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    
    glCall(glDrawArrays(GL_TRIANGLES, 0, 6));

    glCall(glBindTexture(GL_TEXTURE_2D, 0));
    glCall(glDisableVertexAttribArray(vertArrayIndex));
    glCall(glDisableVertexAttribArray(1));
    glCall(glBindVertexArray(0));

    glCall(glDisable(GL_BLEND));
    
    shader.Deactivate();
    glCall(glDeleteBuffers(1, &vboTextQuad));
    glCall(glDeleteVertexArrays(1, &vertArray));
}


