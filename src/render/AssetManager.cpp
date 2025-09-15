//
// Created by Lecka on 15/09/2025.
//

#include "AssetManager.h"
namespace gfx::assets {
    std::unordered_map<Materials, std::shared_ptr<Material> > AssetManager::m_material_cache;
    std::unordered_map<Meshes, std::shared_ptr<Mesh> > AssetManager::m_mesh_cache;
}
