/**************************************************************************************************************
* Debugger - Code
*
* A class used to debug bounding boxes and raycasts (Draws either one in the worldspace)
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "Debugger.h"

void Debugger::BoundingBoxDebug(const Camera* cam, const glm::vec3& meshPos, const BoundingBox& box) const
{
    shader.Activate();

    glm::mat4 modelMatrix = glm::mat4(1);

    // Adjust modelMatrix based on the bounding box position, rotation, and scale
    modelMatrix = glm::translate(modelMatrix, box.center);

    shader.SetMat4Attrib("modelMatrix", modelMatrix);
    shader.SetMat4Attrib("viewMatrix", cam->GetViewMatrix());
    shader.SetMat4Attrib("projectionMatrix", cam->GetProjectionMatrix());

    DebugDrawBoundingBox(box, meshPos);

    shader.Deactivate();
}

void Debugger::DebugDrawBoundingBox(const BoundingBox& box, const glm::vec3& meshPos) const
{
    GLuint vao, vbo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Define vertices for the bounding box
    const glm::vec3 vertices[] =
    {
        box.min - meshPos,
        glm::vec3(box.max.x, box.min.y, box.min.z) - meshPos,
        glm::vec3(box.max.x, box.min.y, box.max.z) - meshPos,
        glm::vec3(box.min.x, box.min.y, box.max.z) - meshPos,
        glm::vec3(box.min.x, box.max.y, box.min.z) - meshPos,
        glm::vec3(box.max.x, box.max.y, box.min.z) - meshPos,
        box.max - meshPos,
        glm::vec3(box.min.x, box.max.y, box.max.z) - meshPos
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Draw the bounding box
    glDrawArrays(GL_LINE_STRIP, 0, 8);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}



void Debugger::RayDebug(const Camera* cam, const Raycast::Ray& ray) const
{
    shader.Activate();

    glm::mat4 modelMatrix = glm::mat4(1);

    modelMatrix = translate(modelMatrix, transform.position);

    modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.x * 180 / M_PI), { 1,0,0 });
    modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.y * 180 / M_PI), { 0,1,0 });
    modelMatrix = rotate(modelMatrix, static_cast<float>(transform.rotation.z * 180 / M_PI), { 0,0,1 });

    modelMatrix = scale(modelMatrix, transform.scale);

    shader.SetMat4Attrib("modelMatrix", modelMatrix);
    shader.SetMat4Attrib("viewMatrix", cam->GetViewMatrix());
    shader.SetMat4Attrib("projectionMatrix", cam->GetProjectionMatrix());

    // Assuming DebugDrawRay doesn't change shader state, you can call it directly
    Raycast::DebugDrawRay(ray);

    shader.Deactivate();
}
