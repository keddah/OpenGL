#include "Material.h"



Material::Material(Shader& _shader) : shader(_shader)
{
    NewTexture("sdf");
}

void Material::NewTexture(std::string filePath)
{
    // image_bytes = stbi_load(filePath &tex_width, &tex_height, &channelCount, 0);
    image_bytes = stbi_load("Images/download.png", &tex_width, &tex_height, &channelCount, 0);
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
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    // Upload texture data
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGBA8, GL_UNSIGNED_BYTE, image_bytes));
    glCall(glGenerateMipmap(GL_TEXTURE_2D));

    // Clean up
    stbi_image_free(image_bytes);
    UnbindTexture();

    // Activate shader and set texture unit
    shader.Activate();
    shader.SetIntAttrib("tex0", 0);
}
