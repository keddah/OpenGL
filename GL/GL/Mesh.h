#pragma once
#include <glew.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include <random>

#include "Camera.h"
#include "Material.h"
#include "Rendering/BufferArrayManager.h"
#include "Rendering/Shader.h"

struct BoundingBox
{
    glm::vec3 min;    
    glm::vec3 max;    
    glm::vec3 center;    
};

class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<GLfloat>& _vertices, const std::vector<GLuint>& _indices, Camera& camera);
    ~Mesh() { delete baManager; delete mat; }
    
    void Render() const;
    void Update(float deltaTime);

    void SetPosition(const glm::vec3 newVal) { transform.position = newVal; }
    void SetPosition(const float x, const float y, const float z) { transform.position = {x,y,z}; }

    void AddPosition(const glm::vec3 newVal) { transform.position += newVal; }
    void AddPosition(const float x, const float y, const float z) { transform.position += glm::vec3(x,y,z); }
    
    void SetRotation(const glm::vec3 newVal) { transform.rotation = newVal; }
    void SetRotation(const float x, const float y, const float z) { transform.rotation = {x,y,z}; }
    
    void AddRotation(const glm::vec3 newVal) { transform.rotation += newVal; }
    void AddRotation(const float x, const float y, const float z) { transform.rotation += glm::vec3(x,y,z); }
    
    void SetScale(const glm::vec3 newVal) { transform.scale = newVal; }
    void SetScale(const float x, const float y, const float z) { transform.scale = {x,y,z}; }

    glm::vec3 GetPosition() const { return transform.position; }
    glm::vec3 GetRotation() const { return transform.rotation; }
    glm::vec3 GetScale() const { return transform.scale; }


    void SetVibility(const bool newVal) { visible = newVal; }
    void SetCollision (const bool newVal) { collisions_enabled = newVal; }
    
private:
    void InitShaders();
    
    BoundingBox CalculateAABoundingBox(const std::vector<GLfloat>& vertices) const;

    struct 
    {
        glm::vec3 position = {};        
        glm::vec3 rotation = {};        
        glm::vec3 scale = {1,1,1};        
    } transform;
    
    Shader shader;
    Material* mat;
    
    struct Vertex
    {
        std::vector<GLfloat> position;        
        glm::vec4 colour;        
    };
    

    BufferArrayManager* baManager;
    
    std::vector<GLfloat> vertices;
    std::vector<Vertex> vertexes;
    std::vector<GLuint> indices;

    GLint vertArrayIndex = -1;

    Camera& rCam;
    
    bool visible = true;
    bool collisions_enabled = true;
};
