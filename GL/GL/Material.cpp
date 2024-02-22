/**************************************************************************************************************
* Material - Code
*
* Creates textures from a given image filepath and applies the colour/normal map texture to the mesh that creates an instance of this class.
* 
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "Material.h"

#include <string>

// Always Base colour  -->  Normal
Material::Material(const std::vector<std::string>& matPath) : texturePaths(matPath)
{
    // Generate texture ID
    glCall(glGenTextures(1, &colour_texture));
    
    // Activate texture unit and bind texture
    glCall(glActiveTexture(GL_TEXTURE0));
    glCall(glBindTexture(GL_TEXTURE_2D, colour_texture));

    glCall(glGenTextures(1, &normal_texture));
    glCall(glActiveTexture(GL_TEXTURE1));
    glCall(glBindTexture(GL_TEXTURE_2D, normal_texture));
    
    shader.Init();

    // Dividing by a byte to get the size of the array
    for(int i = 0; i < matPath.size(); i++)
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
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

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

void Material:: BindTextures(const GLint texIndex) const
{
    // If trying to bind a Normal map texture when one wasn't  provided... return
    if(texIndex == 1 && texturePaths.size() < 2) return;
    
    GLuint toBind;
    GLint texture;
    bool normalPresent = false;
    
    switch (texIndex)
    {
    case 0:
        toBind = colour_texture;
        texture = GL_TEXTURE0 + texIndex;
        break;

    case 1:
        toBind = normal_texture;
        texture = GL_TEXTURE0 + texIndex;
        normalPresent = true;
        break;
        
    default:
        toBind = colour_texture;
        texture = GL_TEXTURE0 + texIndex;
        break;
    }
    
    glCall(glActiveTexture(texture));
    glCall(glBindTexture(GL_TEXTURE_2D, toBind));
    shader.Activate();
    shader.SetIntAttrib("tex" + std::to_string(texIndex), texIndex);
    shader.SetBoolAttrib("normalPresent", normalPresent);

    shader.SetVec2Attrib("uvScale", uvScale);
    shader.SetFloatAttrib("specularStrength", specular);
}
