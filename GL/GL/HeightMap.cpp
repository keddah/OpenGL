#include "HeightMap.h"

HeightMap::HeightMap(string filePath)
{
    int tex_width, tex_height;
    
    unsigned char* heigt_map = stbi_load(filePath.c_str(), &tex_width, &tex_height, nullptr, 4);
    if(!heigt_map)
    {
        print("Unable to load image - possible bad filePath")
        return;
    }

    constexpr float widthScale = 2;
    constexpr float heightScale = 1;

    for(int i = 0; i < tex_height; i++)
    {
        for(int j = 0; j < tex_width; j++)
        {
            // int index = (i * tex_width + j) * components ;
        }
    }
    
    stbi_image_free(heigt_map);
}
