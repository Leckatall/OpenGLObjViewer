//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_WORLD_H
#define OPENGLOBJVIEWER_WORLD_H

#include <algorithm>
#include <vector>
#include <memory>
#include <optional>

#include "Entity.h"
#include "../render/renderer.h"

enum class EntityType {
    ENVIRONMENT,
    TARGET
};

struct EntityParams {
    gfx::assets::Meshes mesh{gfx::assets::Meshes::CUBE};
    gfx::assets::Materials material{gfx::assets::Materials::WHITE};
    glm::vec3 position{0.0f};
    gfx::assets::Transform transform{};

    struct Patch {
        std::optional<gfx::assets::Meshes> mesh;
        std::optional<gfx::assets::Materials> material;
        std::optional<glm::vec3> position;
        std::optional<gfx::assets::Transform> transform;
    };

    EntityParams override(const Patch &p) const {
        EntityParams r = *this;
        if (p.mesh) r.mesh = *p.mesh;
        if (p.material) r.material = *p.material;
        if (p.position) r.position = *p.position;
        if (p.transform) r.transform = *p.transform;
        return r;
    }
};

inline std::unordered_map<EntityType, EntityParams> DEFAULT_ENTITY_PARAMS = {
    {
        EntityType::ENVIRONMENT, {
            gfx::assets::Meshes::CUBE,
            gfx::assets::Materials::GREY_BRICK,
            glm::vec3(0.0f),
            {{10.0f, 5.0f, 7.0f}, glm::vec3(0.0f)},
        }
    },
    {
        EntityType::TARGET, {
            gfx::assets::Meshes::SPHERE,
            gfx::assets::Materials::RED
        }
    }
};

class World {
public:
    // Constructor and Destructor
    World();

    void initialise();

    // Entity management
    std::shared_ptr<Entity> createEntity(EntityType type, EntityParams::Patch overrides = {});

    void removeEntity(const std::shared_ptr<Entity> &entity);

    void update(float deltaTime);

    // Render the world
    void render(Renderer &renderer);

private:
    // List of all entities in the world
    std::vector<std::shared_ptr<Entity> > m_entities;
};


#endif //OPENGLOBJVIEWER_WORLD_H
