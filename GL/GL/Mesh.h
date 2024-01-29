#pragma once
#include <glew.h>
#include <vector>
#include <iostream>
#include <gtc/type_ptr.hpp>
#include <random>

#include "Camera.h"
#include "Rendering/Buffers_Array.h"
#include "Rendering/Shader.h"

#define print(x) { std::cerr << x << std::endl; }


class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<GLfloat>& _vertices, const std::vector<GLuint>& _indices, Camera& camera);
    ~Mesh() { delete v_array; }
    
    void Render();
    void Update(float deltaTime);

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


    void SetVibility(const bool newVal) { visible = newVal; }
    void SetCollision (const bool newVal) { collisions_enabled = newVal; }
    
private:
    void InitVertices();
    bool InitShaders();

    glm::mat4 modelMatrix {1};
    struct 
    {
        glm::vec3 position = {};        
        glm::vec3 rotation = {};        
        glm::vec3 scale = {1,1,1};        
    } transform;
    
    Shader shader;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    // GLuint vertex_array, vertex_buffer, index_buffer;

    VertexBuffer v_buffer;
    IndexBuffer i_buffer;
    VertexArray* v_array;
    
    GLint vertexPosIndex = -1;

    Camera& rCam;
    
    GLint model_matrix_address = -1;
    GLint view_matrix_address = -1;
    GLint projection_matrix_address = -1;

    bool visible = true;
    bool collisions_enabled = true;
};
