#include "Material.h"

#include <string>

// Always Base colour  -->  Normal
Material::Material(Shader& _shader, const std::string matPath[]) : shader(_shader)
{
    // Generate texture ID
    glCall(glGenTextures(1, &colour_texture));
    glCall(glGenTextures(1, &normal_texture));
    
    // Activate texture unit and bind texture
    glCall(glActiveTexture(GL_TEXTURE0));
    glCall(glBindTexture(GL_TEXTURE_2D, colour_texture));
    
    glCall(glActiveTexture(GL_TEXTURE1));
    glCall(glBindTexture(GL_TEXTURE_2D, normal_texture));
    
    for(int i = 0; i < sizeof(matPath) / 8; i++)
    {
        unsigned char* image_bytes = stbi_load(matPath[i].c_str(), &tex_width, &tex_height, &channelCount, 4);
        if(!image_bytes)
        {
            print("Unable to load image - possible bad filePath")
            return;
        }

        // Set texture parameters
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        // Activate shader and set texture unit
        BindTextures(i);
        
        // Upload texture data
        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_bytes));
        glCall(glGenerateMipmap(GL_TEXTURE_2D));

        // Clean up
        stbi_image_free(image_bytes);
        UnbindTextures();
    }
}

void Material::BindTextures(const GLuint texIndex) const
{
    GLuint toBind;
    GLint texture;
    switch (texIndex)
    {
    case 0:
        toBind = colour_texture;
        texture = GL_TEXTURE0;
        break;

    case 1:
        toBind = normal_texture;
        texture = GL_TEXTURE1;
        break;
        
    default:
        toBind = colour_texture;
        texture = GL_TEXTURE0;
        break;
    }
    
    glCall(glActiveTexture(texture));
    glCall(glBindTexture(GL_TEXTURE_2D, toBind));
    shader.Activate();
    shader.SetIntAttrib("tex" + std::to_string(texIndex), texIndex);
}
