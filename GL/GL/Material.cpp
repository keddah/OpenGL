#include "Material.h"

Material::Material(Shader& _shader, const std::string& matPath) : shader(_shader)
{
    NewTexture(matPath);
}

void Material::NewTexture(const std::string& filePath)
{
    image_bytes = stbi_load(filePath.c_str(), &tex_width, &tex_height, &channelCount, 4);
    if(!image_bytes)
    {
        print("Unable to load image - possible bad filePath")
        return;
    }

    // Generate texture ID
    glCall(glGenTextures(1, &colour_texture));

    // Activate texture unit and bind texture
    glCall(glActiveTexture(GL_TEXTURE0));
    BindTexture();

    // Set texture parameters
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    const bool opacity = channelCount > 3;

    // Activate shader and set texture unit
    shader.Activate();
    shader.SetIntAttrib("tex0", 0);
    
    // Upload texture data
    //glCall(glTexImage2D(GL_TEXTURE_2D, 0, opacity ? GL_RGBA8 : GL_RGB8, tex_width, tex_height, 0, opacity ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image_bytes));
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_width, tex_height, 0,GL_RGBA, GL_UNSIGNED_BYTE, image_bytes));
    //unsigned char pixel[] { 255, 0, 255 };
    //glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel));
    glCall(glGenerateMipmap(GL_TEXTURE_2D));

    // Clean up
    stbi_image_free(image_bytes);
    UnbindTexture();

}
