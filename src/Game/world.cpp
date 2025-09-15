//
// Created by Lecka on 13/09/2025.
//

#include "world.h"

#include "../render/AssetManager.h"
#include "../render/material_manager.h"

World::World() {

}

void World::initialise() {
    createEntity(EntityType::ENVIRONMENT);
    createEntity(EntityType::TARGET);
}

std::shared_ptr<Entity> World::createEntity(EntityType type, EntityParams::Patch overrides) {
    EntityParams params = DEFAULT_ENTITY_PARAMS[type].override(overrides);
    gfx::assets::MeshInstance mesh_instance = {params.mesh, params.material, params.transform};
    auto entity = std::make_shared<Entity>(mesh_instance, params.position);
    m_entities.push_back(entity);
    return entity;
}

void World::removeEntity(const std::shared_ptr<Entity> &entity) {
    m_entities.erase(std::ranges::remove(m_entities, entity).begin(), m_entities.end());
}

void World::update(float deltaTime) {
    for (auto& entity : m_entities) {
        entity->update(deltaTime);
    }
}

void World::render(Renderer &renderer) {
    for (const auto& entity : m_entities) {
        renderer.renderEntity(*entity);
    }
}
