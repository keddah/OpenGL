#pragma once
#include <glew.h>
#include <vector>

#include "Shader.h"

class Mesh
{
public:
    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);

    void Render() const;
    
private:
    void InitVertices();
    void InitShaders();
    
    std::vector<GLfloat> vertices;
    GLuint vertex_array, vertex_buffer, element_buffer;
    GLsizei vertex_count;

    Shader shader;
};
