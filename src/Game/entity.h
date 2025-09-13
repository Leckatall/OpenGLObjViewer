//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_ENTITY_H
#define OPENGLOBJVIEWER_ENTITY_H
#include <memory>

#include "glm/vec3.hpp"
#include "../render/mesh.h"
#include "glm/fwd.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/euler_angles.hpp"

class Entity {
public:
    Entity(const std::shared_ptr<Mesh> &mesh, const glm::vec3 pos)
        : m_position(pos), m_mesh(mesh), m_rotation(0.0f), m_scale(1.0f) {
    }

    void setPosition(float x, float y, float z) { m_position = {x, y, z}; }
    const glm::vec3& getPosition() const { return m_position; }

    void rotate(const float pitch, const float yaw, const float roll) {
        m_rotation += glm::vec3(pitch, yaw, roll);
    }

    void scaleBy(const float sx, const float sy, const float sz) {
        m_scale *= glm::vec3(sx, sy, sz);
    }

    void scaleBy(const float s) {
        scaleBy(s, s, s);
    }

    glm::mat4 getMatrix() const {
        const glm::mat4 rotationMatrix = glm::yawPitchRoll(glm::radians(m_rotation.y), glm::radians(m_rotation.x),
                                                     glm::radians(m_rotation.z));
        const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

        return rotationMatrix * scaleMatrix;
    }
    const std::shared_ptr<Mesh>& getMesh() const { return m_mesh; }

    void update(float deltaTime) {}

private:
    glm::vec3 m_position;
    std::shared_ptr<Mesh> m_mesh;
    // rotation and scale might be unique to the entity, but the mesh (defining the geometry and texture) is often shared by many entities
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};


#endif //OPENGLOBJVIEWER_ENTITY_H