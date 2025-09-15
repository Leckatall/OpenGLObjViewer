//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_ENTITY_H
#define OPENGLOBJVIEWER_ENTITY_H
#include <memory>
#include <utility>

#include "glm/vec3.hpp"
#include "../render/mesh.h"
#include "glm/fwd.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "../render/AssetManager.h"
#include "glm/gtx/euler_angles.hpp"



class Entity {
public:
    Entity(gfx::assets::MeshInstance mesh, const glm::vec3 pos)
        : m_position(pos), m_mesh_instance(std::move(mesh)) {
    }

    void setPosition(float x, float y, float z) { m_position = {x, y, z}; }
    [[nodiscard]] const glm::vec3& getPosition() const { return m_position; }

    // void rotate(const float pitch, const float yaw, const float roll) {
    //     m_rotation += glm::vec3(pitch, yaw, roll);
    // }
    //
    // void scaleBy(const float sx, const float sy, const float sz) {
    //     m_scale *= glm::vec3(sx, sy, sz);
    // }
    //
    // void scaleBy(const float s) {
    //     scaleBy(s, s, s);
    // }
    //
    [[nodiscard]] glm::mat4 getMatrix() const {
        const glm::mat4 rotationMatrix = glm::yawPitchRoll(glm::radians(m_mesh_instance.transform.rotation.y), glm::radians(m_mesh_instance.transform.rotation.x),
                                                     glm::radians(m_mesh_instance.transform.rotation.z));
        const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_mesh_instance.transform.scale);

        return rotationMatrix * scaleMatrix;
    }
    [[nodiscard]] gfx::assets::MeshInstance getMeshInstance() const { return m_mesh_instance; }

    void update(float deltaTime) {}

private:
    glm::vec3 m_position;
    gfx::assets::MeshInstance m_mesh_instance;
    // rotation and scale might be unique to the entity, but the mesh (defining the geometry and texture) is often shared by many entities
};


#endif //OPENGLOBJVIEWER_ENTITY_H