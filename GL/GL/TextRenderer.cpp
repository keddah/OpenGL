#include "TextRenderer.h"

#include <ext/matrix_clip_space.hpp>

void TextRenderer::Draw(const glm::mat4& projectionpro) const
{
    const Vertex verts[] =
    {
        {{drawPos.x, drawPos.y, 0}, {0,0,0}, {0,1}},
        {{drawPos.x, drawPos.y + size.y, 0}, {0,0,0}, {0,0}},
        {{drawPos.x + size.x, drawPos.y + size.y, 0}, {0,0,0}, {1,0}},

        {{drawPos.x + size.x, drawPos.y + size.y, 0}, {0,0,0}, {1,0}},
        {{drawPos.x + size.x, drawPos.y, 0}, {0,0,0}, {1,1}},
        {{drawPos.x, drawPos.y, 0}, {0,0,0}, {0,1}}
    };

    GLuint vertBuffer;
    GLuint vertArray;
    
    glCall(glGenVertexArrays(1, &vertArray));
    glCall(glBindVertexArray(vertArray));

    glCall(glGenBuffers(1, &vertBuffer));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vertBuffer))
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));

    
    glCall(glEnable(GL_CULL_FACE))
    
    shader.Activate();

    const glm::mat4 projection = glm::ortho(0,1920, 0, 1080);
	shader.SetMat4Attrib("projectionMatrix", projection);

    // Bind the buffer
    glCall(glBindBuffer(GL_ARRAY_BUFFER, vertBuffer));
    
    // Enable the vertex position shader attrib
    glCall(glEnableVertexAttribArray(0));

    // Assign a value to the vertex position to give to the shader
    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));
    
    // Do the same for the UV address....
    glCall(glEnableVertexAttribArray(1));
    glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)));

    glCall(glActiveTexture(GL_TEXTURE0));
    shader.SetIntAttrib("sampler", 0);
    glCall(glBindTexture(GL_TEXTURE_2D, texture));

    // DRAW
    glCall((glDrawArrays(GL_TRIANGLES, 0, 6)));

    // Unbind everything
    glCall(glBindTexture(GL_TEXTURE_2D, 0));

    glCall(glDisableVertexAttribArray(vertPosAddress));
    glCall(glDisableVertexAttribArray(uvAddress));

    shader.Deactivate();

    glCall(glDeleteBuffers(1, &vertBuffer));
}

void TextRenderer::SetText(const std::string& toDisplay, const std::string& _fontPath)
{
    text = toDisplay;
    fontPath = _fontPath;
    
    TTF_Font* font = TTF_OpenFont(_fontPath.c_str(), fontSize);

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

    for(int i = 0; i < size.y * .5f; i++)
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
}

void TextRenderer::CreateBufferManager()
{
//     std::vector<GLfloat> verts =
//         {
//         {{drawPos.x, drawPos.y, 0}, {0,0,0}, {0,1}},
//         {{drawPos.x, drawPos.y + size.y, 0}, {0,0,0}, {0,0}},
//         {{drawPos.x + size.x, drawPos.y + size.y, 0}, {0,0,0}, {1,0}},
//
//         {{drawPos.x + size.x, drawPos.y + size.y, 0}, {0,0,0}, {1,0}},
//         {{drawPos.x + size.x, drawPos.y, 0}, {0,0,0}, {1,1}},
//         {{drawPos.x, drawPos.y, 0}, {0,0,0}, {0,1}}
//         };
//
//     std::vector<GLuint> indices =
//     {
//         0, 1, 2,
//         1, 3 ,2
//         // 4, 0, 
//         
//     };
    
    
    // baManager = new BufferArrayManager(verts, indices);
}
