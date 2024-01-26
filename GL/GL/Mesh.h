#pragma once
#include <glew.h>
#include <vector>

#include "Camera.h"
#include "Rendering/Shader.h"

class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, Camera& camera);

    void Render() const;

    void SetPosition(const glm::vec3 newVal) { transform.position = newVal; }
    void SetPosition(const float x, const float y, const float z) { transform.position = {x,y,z}; }

    void SetRelativePosition(const glm::vec3 newVal) { transform.position += newVal; }
    void SetRelativePosition(const float x, const float y, const float z) { transform.position += glm::vec3(x,y,z); }
    
    void SetRotation(const glm::vec3 newVal) { transform.rotation = newVal; }
    void SetRotation(float x, float y, float z) { transform.rotation = {x,y,z}; }
    
    void SetRelativeRotation(const glm::vec3 newVal) { transform.rotation += newVal; }
    void SetRelativeRotation(const float x, const float y, const float z) { transform.rotation += glm::vec3(x,y,z); }
    
    void SetScale(const glm::vec3 newVal) { transform.scale = newVal; }
    void SetScale(const float x, const float y, const float z) { transform.position = {x,y,z}; }

    glm::vec3 GetPosition() const { return transform.position; }
    glm::vec3 GetRotation() const { return transform.rotation; }
    glm::vec3 GetScale() const { return transform.scale; }
    
private:
    void InitVertices(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
    bool InitShaders();

    struct 
    {
        glm::vec3 position = {};        
        glm::vec3 rotation = {};        
        glm::vec3 scale = {1,1,1};        
    } transform;
    
    Shader shader;
    std::vector<GLfloat> vertices;
    GLuint vertex_array, vertex_buffer, index_buffer;
    GLsizei index_count;

    GLint vertexPosIndex = -1;

    Camera& rCam;
    
    GLint model_matrix_address = -1;
    GLint view_matrix_address = -1;
    GLint projection_matrix_address = -1;
};
