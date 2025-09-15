// //
// // Created by Lecka on 13/09/2025.
// //
//
// #ifndef OPENGLOBJVIEWER_MATERIAL_MANAGER_H
// #define OPENGLOBJVIEWER_MATERIAL_MANAGER_H
// #include <memory>
// #include <string>
// #include <unordered_map>
// #include <functional>
//
//
// #include "AssetManager.h"
// #include "texture_manager.h"
//
// // struct DefaultMaterialsHash {
// //     std::size_t operator()(DefaultMaterials material) const {
// //         return static_cast<std::size_t>(material);
// //     }
// // };
//
// inline std::unordered_map<gfx::assets::Materials, const char *> textureFile = {
//     {gfx::assets::Materials::GREY_BRICK, "grey-brick.jpg"}
// };
//
// // inline std::unordered_map<DefaultMaterials, glm::vec4> materialColour = {
// //     {DefaultMaterials::WHITE, {1.0f, 1.0f, 1.0f, 1.0f}},
// //     {DefaultMaterials::BLACK, {0.0f, 0.0f, 0.0f, 1.0f}},
// //     {DefaultMaterials::RED, {1.0f, 0.0f, 0.0f, 1.0f}},
// // };
//
// class MaterialManager {
// public:
//     static MaterialManager &getInstance() {
//         static MaterialManager instance;
//         return instance;
//     }
//
//     static std::shared_ptr<gfx::assets::Material> getMaterial(const gfx::assets::Materials name) {
//         if (auto it = material_cache.find(name); it != material_cache.end()) {
//             return it->second; // Return cached material
//         }
//         std::shared_ptr<gfx::assets::Material> newMaterial;
//         switch (name) {
//             case DefaultMaterials::WHITE:
//             case DefaultMaterials::BLACK:
//             case DefaultMaterials::RED:
//                 newMaterial = createColourMaterial(name);
//                 break;
//             case DefaultMaterials::GREY_BRICK:
//                 newMaterial = createTextureMaterial(name);
//                 break;
//         }
//
//         // Create and cache the material if it doesn't exist
//         material_cache[name] = newMaterial;
//         return newMaterial;
//     }
//
// private:
//     MaterialManager() {
//     }
//
//     ~MaterialManager() {
//     }
//
//     static std::shared_ptr<gfx::assets::Material> createTextureMaterial(const gfx::assets::Materials name) {
//         auto texture = gfx::assets::TextureManager::loadTexture(textureFile[name]);
//         return std::make_shared<gfx::assets::Material>(texture);
//     }
//
//     static std::shared_ptr<gfx::assets::Material> createColourMaterial(const gfx::assets::Materials name) {
//         return std::make_shared<gfx::assets::Material>(materialColour[name]);
//     }
//
//     static std::unordered_map<gfx::assets::Materials, std::shared_ptr<gfx::assets::Material> > material_cache;
// };
//
//
// #endif //OPENGLOBJVIEWER_MATERIAL_MANAGER_H
