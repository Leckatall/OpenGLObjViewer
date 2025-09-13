//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_MATERIAL_MANAGER_H
#define OPENGLOBJVIEWER_MATERIAL_MANAGER_H
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>


#include "material.h"
#include "texture_manager.h"

enum class DefaultMaterials {
    WHITE,
    BLACK,
    RED,
    GREY_BRICK
};

// struct DefaultMaterialsHash {
//     std::size_t operator()(DefaultMaterials material) const {
//         return static_cast<std::size_t>(material);
//     }
// };

inline std::unordered_map<DefaultMaterials, const char *> textureFile = {
    {DefaultMaterials::GREY_BRICK, "grey-brick.jpg"}
};

inline std::unordered_map<DefaultMaterials, glm::vec4> materialColour = {
    {DefaultMaterials::WHITE, {1.0f, 1.0f, 1.0f, 1.0f}},
    {DefaultMaterials::BLACK, {0.0f, 0.0f, 0.0f, 1.0f}},
    {DefaultMaterials::RED, {1.0f, 0.0f, 0.0f, 1.0f}},
};

class MaterialManager {
public:
    static MaterialManager &getInstance() {
        static MaterialManager instance;
        return instance;
    }

    static std::shared_ptr<Material> getMaterial(const DefaultMaterials name) {
        if (auto it = material_cache.find(name); it != material_cache.end()) {
            return it->second; // Return cached material
        }
        std::shared_ptr<Material> newMaterial;
        switch (name) {
            case DefaultMaterials::WHITE:
            case DefaultMaterials::BLACK:
            case DefaultMaterials::RED:
                newMaterial = createColourMaterial(name);
                break;
            case DefaultMaterials::GREY_BRICK:
                newMaterial = createTextureMaterial(name);
                break;
        }

        // Create and cache the material if it doesn't exist
        material_cache[name] = newMaterial;
        return newMaterial;
    }

private:
    MaterialManager() {
    }

    ~MaterialManager() {
    }

    static std::shared_ptr<Material> createTextureMaterial(const DefaultMaterials name) {
        auto texture = TextureManager::loadTexture(*textureFile[name]);
        return std::make_shared<Material>(texture);
    }

    static std::shared_ptr<Material> createColourMaterial(const DefaultMaterials name) {
        return std::make_shared<Material>(materialColour[name]);
    }

    static std::unordered_map<DefaultMaterials, std::shared_ptr<Material> > material_cache;
};


#endif //OPENGLOBJVIEWER_MATERIAL_MANAGER_H
