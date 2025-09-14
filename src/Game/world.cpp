//
// Created by Lecka on 13/09/2025.
//

#include "world.h"

#include "../render/material_manager.h"

World::World() {

}

void World::initialise() {
    createEntity();
}

std::shared_ptr<Entity> World::createEntity() {
    auto geometry = MeshGenerator::generateShape(MeshGenerator::ShapeType::Cube);
    auto material = MaterialManager::getInstance().getMaterial(DefaultMaterials::BLACK);
    auto mesh = std::make_shared<Mesh>(geometry, material);
    auto entity = std::make_shared<Entity>(mesh, glm::vec3(0.0f, 0.0f, 0.0f));
    //entity->scaleBy(4, 1, 2);
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
