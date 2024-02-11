#include "HeightMap.h"

HeightMap::HeightMap(string filePath)
{
    int tex_width, tex_height;
    
    unsigned char* height_map = stbi_load(filePath.c_str(), &tex_width, &tex_height, nullptr, 4);
    if(!height_map)
    {
        print("Unable to load image - possible bad filePath")
        return;
    }

    constexpr float widthScale = 2;
    constexpr float heightScale = 1;

    for(int row = 0; row < tex_height; row++)
    {
        for(int col = 0; col < tex_width; col++)
        {
            const int index = row * tex_width + col;
            const char r = height_map[index + 0];
            const char g = height_map[index + 1];
            const char b = height_map[index + 2];
            const float height = (r + g + b) / 3;

            const float x = col / (tex_width - 1) * widthScale;
            const float y = (height / 255) * heightScale;
            const float z = row / (tex_height - 1) * widthScale;
        }
    }
    
    stbi_image_free(height_map);
}
