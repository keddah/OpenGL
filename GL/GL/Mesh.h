#pragma once
#include <glew.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include <gtc/quaternion.hpp>
#include <random>

#include "BoundingBox.h"
#include "Camera.h"
#include "Material.h"
#include "Rendering/BufferArrayManager.h"
#include "Rendering/Shader.h"

class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<GLfloat>& vertexData, const std::vector<GLuint>& _indices);
    ~Mesh() { delete baManager; delete mat; }
    
    void Render(Camera& cam) const;

    void SetPosition(const glm::vec3 newVal) { transform.position = newVal;  CalculateAABoundingBox(); }
    void SetPosition(const float x, const float y, const float z) { transform.position = {x,y,z}; CalculateAABoundingBox(); }

    void AddPosition(const glm::vec3 newVal) { transform.position += newVal;  CalculateAABoundingBox(); }
    void AddPosition(const float x, const float y, const float z) { transform.position += glm::vec3(x,y,z); CalculateAABoundingBox(); }
    
    void SetRotation(const glm::vec3 newVal) { transform.rotation = newVal;  CalculateAABoundingBox(); }
    void SetRotation(const float x, const float y, const float z) { transform.rotation = {x,y,z};  CalculateAABoundingBox(); }
    
    void AddRotation(const glm::vec3 newVal) { transform.rotation += newVal;  CalculateAABoundingBox(); }
    void AddRotation(const float x, const float y, const float z) { transform.rotation += glm::vec3(x,y,z);  CalculateAABoundingBox(); }
    
    void SetScale(const glm::vec3 newVal) { transform.scale = newVal;  CalculateAABoundingBox(); }
    void SetScale(const float x, const float y, const float z) { transform.scale = {x,y,z};  CalculateAABoundingBox(); }

    glm::vec3 GetPosition() const { return transform.position; }
    glm::vec3 GetRotation() const { return transform.rotation; }
    glm::vec3 GetScale() const { return transform.scale; }
    BoundingBox GetBoundingBox() const { return boundingBox; }

    void SetVisibility(const bool newVal) { visible = newVal; }
    bool IsVisible() const { return visible; }
    
    void SetCollision (const bool newVal) { collisions_enabled = newVal; }
    bool IsCollisions() const { return collisions_enabled; }

private:
    void InitShaders();
    std::vector<GLfloat> GetVertexData() const
    {
        std::vector<GLfloat> data;
        for(auto& vert : vertices)
        {
            for(auto& pos : vert.position) data.push_back(pos);
            for(auto& colour : vert.colour) data.push_back(colour);
            for(auto& uv : vert.texCoords) data.push_back(uv);
        }
        return data;
    }
    void CalculateAABoundingBox();

    struct 
    {
        glm::vec3 position = {};        
        glm::vec3 rotation = {};        
        glm::vec3 scale = {1,1,1};        
    } transform;

    BoundingBox boundingBox;
    
    Shader shader;
    Material* mat;
    
    

    BufferArrayManager* baManager;
    
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    GLint vertArrayIndex = -1;

    bool visible = true;
    bool collisions_enabled = true;
};
