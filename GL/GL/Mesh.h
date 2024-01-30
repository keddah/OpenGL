#pragma once
#include <glew.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include <random>

#include "Camera.h"
#include "Rendering/BufferArrayManager.h"
#include "Rendering/Shader.h"

class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<GLfloat>& _vertices, const std::vector<GLuint>& _indices, Camera& camera);
    ~Mesh() { delete baManager; }
    
    void Render() const;
    void Update(float deltaTime);

    void SetPosition(const glm::vec3 newVal) { transform.position = newVal; UpdateVertices(); }
    void SetPosition(const float x, const float y, const float z) { transform.position = {x,y,z}; UpdateVertices(); }

    void SetRelativePosition(const glm::vec3 newVal) { transform.position += newVal; UpdateVertices(); }
    void SetRelativePosition(const float x, const float y, const float z) { transform.position += glm::vec3(x,y,z); UpdateVertices(); }
    
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
    void InitShaders();

    // Mainly the position
    void UpdateVertices();

    struct 
    {
        glm::vec3 position = {};        
        glm::vec3 rotation = {};        
        glm::vec3 scale = {1,1,1};        
    } transform;
    
    Shader shader;

    struct Vertex
    {
        std::vector<GLfloat> position;        
        glm::vec4 colour;        
    };
    
    std::vector<GLfloat> vertices;

    BufferArrayManager* baManager;
    
    std::vector<Vertex> vertexes;
    
    std::vector<GLuint> indices;

    GLint vertexPosIndex = -1;

    Camera& rCam;
    
    GLint model_matrix_address = -1;
    GLint view_matrix_address = -1;
    GLint projection_matrix_address = -1;

    bool visible = true;
    bool collisions_enabled = true;
};
