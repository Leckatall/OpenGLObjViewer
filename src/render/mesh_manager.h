// //
// // Created by Lecka on 13/09/2025.
// //
//
// #ifndef OPENGLOBJVIEWER_MESH_MANAGER_H
// #define OPENGLOBJVIEWER_MESH_MANAGER_H
// #include <cstddef>
// #include <memory>
// #include <unordered_map>
//
// #include "mesh.h"
//
//
// class MeshManager {
// public:
//     static MeshManager getInstance() {
//         static MeshManager instance;
//         return instance;
//     }
//     std::shared_ptr<Mesh> getMesh(const MeshGenerator::Geometry& geometry, const std::shared_ptr<Material>& material) {
//         // Generate a unique hash for the geometry + material combination
//         std::size_t hash = computeHash(geometry, material);
//
//         // Check if the mesh exists in the cache
//         auto it = meshCache.find(hash);
//         if (it != meshCache.end()) {
//             return it->second; // Return cached mesh
//         }
//
//         // Create and cache the new mesh
//         auto newMesh = std::make_shared<Mesh>(geometry, material);
//         meshCache[hash] = newMesh;
//         return newMesh;
//     }
//
// private:
//     MeshManager() {}
//     ~MeshManager() {}
//
//     MeshManager(const MeshManager&) = delete;
//     MeshManager& operator=(const MeshManager&) = delete;
//
//     // Cache for storing meshes
//     std::unordered_map<std::size_t, std::shared_ptr<Mesh>> meshCache;
//
//     // Custom hash function to combine geometry and material
//     static std::size_t computeHash(const MeshGenerator::Geometry& geometry, const std::shared_ptr<Material>& material) {
//         std::size_t seed = 0;
//
//         // Hash geometry (replace with your actual geometry hashing logic)
//         seed ^= std::hash<MeshGenerator::Geometry>()(geometry);
//
//         // Hash material (assumes material pointer is hashable; modify as needed)
//         seed ^= std::hash<std::shared_ptr<Material>>()(material) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//
//         return seed;
//     }
// };
//
//
// #endif //OPENGLOBJVIEWER_MESH_MANAGER_H