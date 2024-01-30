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
    glGenTextures(1, &colour_texture);

    // Activate texture unit and bind texture
    glActiveTexture(GL_TEXTURE0);
    BindTexture();

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, tex_width, tex_height, 0, GL_RGBA8, GL_UNSIGNED_BYTE, image_bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        print("Error during texture setup: " << gluErrorString(error));
        // Handle or log the error accordingly
    }

    // Clean up
    stbi_image_free(image_bytes);
    UnbindTexture();

    // Activate shader and set texture unit
    shader.Activate();
    shader.SetIntAttrib("tex0", 0);
}
