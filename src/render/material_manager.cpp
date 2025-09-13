//
// Created by Lecka on 13/09/2025.
//

#include "material_manager.h"

std::unordered_map<DefaultMaterials, std::shared_ptr<Material> > MaterialManager::material_cache;
