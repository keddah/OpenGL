#pragma once
#include <glew.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include <gtc/quaternion.hpp>
#include <random>

#include "Rendering/BufferArrayManager.h"
#include "Transform.h"
#include "BoundingBox.h"
#include "Camera.h"
#include "Debugger.h"
#include "Material.h"
#include "Rendering/Shader.h"
#include "Light.h"

class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<GLfloat>& vertexData, const std::vector<GLuint>& _indices, const std::vector<std::string>& materialPath);
    ~Mesh() { delete baManager; delete mat; }
    
    void Render(Camera* cam, const Light& light) const;

    void SetPosition(const glm::vec3& newVal) { transform.position = newVal;  CalculateAABoundingBox(); }
    void SetPosition(const float x, const float y, const float z) { transform.position = {x,y,z}; CalculateAABoundingBox(); }

    void AddPosition(const glm::vec3& newVal) { transform.position += newVal;  CalculateAABoundingBox(); }
    void AddPosition(const float x, const float y, const float z) { transform.position += glm::vec3(x,y,z); CalculateAABoundingBox(); }
    
    void SetRotation(const glm::vec3& newVal) { transform.rotation = newVal;  CalculateAABoundingBox(); }
    void SetRotation(const float x, const float y, const float z) { transform.rotation = {x,y,z};  CalculateAABoundingBox(); }
    
    void LookAtRotation(const glm::mat4& matrix);

    void AddRotation(const glm::vec3& newVal) { transform.rotation += newVal;  CalculateAABoundingBox(); }
    void AddRotation(const float x, const float y, const float z) { transform.rotation += glm::vec3(x,y,z);  CalculateAABoundingBox(); }
    
    void SetScale(const glm::vec3& newVal) { transform.scale = newVal;  CalculateAABoundingBox(); }
    void SetScale(const float x, const float y, const float z) { transform.scale = {x,y,z};  CalculateAABoundingBox(); }
    void SetScale(const float xyz) { transform.scale = {xyz,xyz,xyz};  CalculateAABoundingBox(); }

    glm::vec3 GetPosition() const { return transform.position; }
    glm::vec3 GetRotation() const { return transform.rotation; }
    glm::vec3 GetScale() const { return transform.scale; }

    void SetBBOffset(const glm::vec3& offset) { bbOffset = offset; }
    BoundingBox GetBoundingBox() const { return boundingBox; }

    void CreateMaterial(const std::vector<std::string>& texturePath);
    void SetVisibility(const bool newVal) { visible = newVal; }
    bool IsVisible() const { return visible; }
    
    void SetCollision (const bool newVal) { collisions_enabled = newVal; }
    bool IsCollisions() const { return collisions_enabled; }

    Transform GetTransform() const { return transform; }
    void SetTransform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) { transform.position = pos; transform.rotation = rot; transform.scale = scale; }
    void SetTransform(const float x, const float y, const float z, const glm::vec3& rot, const glm::vec3& scale) { transform.position = {x,y,z}; transform.rotation = rot; transform.scale = scale; }
    void SetTransform(const glm::vec3& pos, const float x, const float y, const float z, const glm::vec3& scale) { transform.position = pos; transform.rotation = {x,y,z}; transform.scale = scale; }
    void SetTransform(const glm::vec3& pos, const glm::vec3& rot, const float x, const float y, const float z) { transform.position = pos; transform.rotation = rot; transform.scale = {x,y,z}; }
    void SetTransform(const float px, const float py, const float pz, const float rx, const float ry, const float rz, const float sx, const float sy,  const float sz)
    {
        transform.position = {px,py,pz}; transform.rotation = {rx,ry,rz}; transform.scale = {sx,sy,sz};
    }

    void SetMaterialSpecular(const float spec) const { mat->SetSpecular(spec); }
    void SetUvScale(const glm::vec2& scale) const { if(mat) mat->SetUvScale(scale); } 
    void SetUvScale(const float x, const float y) const { if(mat) mat->SetUvScale(x, y); }
    void SetUvScale(const float xy) const { if(mat) mat->SetUvScale(xy, xy); }

private:
    void InitShaders(const std::vector<std::string>& matPath);
    void CalculateAABoundingBox();
    void Lighting(const Camera* cam, const Light& light) const;

    std::vector<GLfloat> GetVertexData() const
    {
        std::vector<GLfloat> data;
        for(auto& vert : vertices)
        {
            for(auto& pos : vert.position) data.push_back(pos);
            for(auto& normal : vert.normals) data.push_back(normal);
            for(auto& uv : vert.texCoords) data.push_back(uv);
        }
        return data;
    }
    
    void Debug(Camera* cam) const;
    
    std::vector<GLuint> indices;
    std::vector<Vertex> vertices;
    BoundingBox boundingBox;

    Debugger debugger;
    Shader shader {"Rendering/Shaders/VertexShader.glsl", "Rendering/Shaders/FragmentShader.glsl"};
    Material* mat;

    Transform transform = {{}, {}, {1,1,1}};

    glm::vec3 bbOffset { 0,0,0};
    
    BufferArrayManager* baManager;
    
    GLint vertArrayIndex = -1;

    bool looking;
    glm::mat4 rotMatrix = glm::mat4(1);

    bool visible = true;
    bool collisions_enabled = true;
};
