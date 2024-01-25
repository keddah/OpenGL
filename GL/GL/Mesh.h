#pragma once
#include <glew.h>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);

    void Render() const;
    
private:
    std::vector<GLfloat> vertices;
    GLuint vertex_array, vertex_buffer, element_buffer;
    GLsizei vertex_count;
};
