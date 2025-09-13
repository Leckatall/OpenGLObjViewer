//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_WORLD_H
#define OPENGLOBJVIEWER_WORLD_H

#include <algorithm>
#include <vector>
#include <memory>
#include "Entity.h"
#include "../render/renderer.h"

class World {
public:
    // Constructor and Destructor
    World();

    void initialise();

    // Entity management
    std::shared_ptr<Entity> createEntity();
    void removeEntity(const std::shared_ptr<Entity>& entity);

    void update(float deltaTime);

    // Render the world
    void render(Renderer& renderer);

private:
    // List of all entities in the world
    std::vector<std::shared_ptr<Entity>> m_entities;
};


#endif //OPENGLOBJVIEWER_WORLD_H