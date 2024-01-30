#include "Material.h"


Material::Material(Shader& _shader) : shader(_shader)
{
    NewTexture("sdf");
}

void Material::NewTexture(std::string filePath)
{
    // image_bytes = stbi_load(filePath &tex_width, &tex_height, &channelCount, 0);
    image_bytes = stbi_load("Images/download.png", &tex_width, &tex_height, &channelCount, 0);
    
    glGenTextures(1, &colour_texture);
    glActiveTexture(GL_TEXTURE0);
    BindTexture();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image_bytes);
    UnbindTexture();

    shader.Activate();
    shader.SetIntAttrib("tex0", 0);
}
