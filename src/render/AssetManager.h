//
// Created by Lecka on 15/09/2025.
//

#ifndef OPENGLOBJVIEWER_ASSETMANAGER_H
#define OPENGLOBJVIEWER_ASSETMANAGER_H
#include <memory>

#include "material_manager.h"
#include "mesh.h"
#include "texture_manager.h"
#include "glm/glm.hpp"

namespace gfx::assets {
    // TODO: Make a mesh struct instead of a class
    // struct Mesh {
    //     uint32_t vao = 0;
    //     uint32_t indexCount = 0;
    //     // plus VBO/IBO handles, bounds, etc.
    // };
    struct Transform {
        glm::vec3 scale{1.0f};
        glm::vec3 rotation{0.0f};
    };

    struct MaterialLighting {
        float kd = 0.8f;
        float F0 = 0.04f;
        float shininess = 64.0f;
        float ambientFactor = 0.1f;
        float ao = 1.0f;
        float emissiveIntensity = 0.0f;
        float alpha = 1.0f;
    };

    struct Material {
        glm::vec3 baseColor{1.0f};
        MaterialLighting lighting{};
        std::shared_ptr<Texture> texture;

        explicit Material(const std::shared_ptr<Texture> &texture) : texture(texture) {
        }

        explicit Material(const glm::vec3 baseColor) : baseColor(baseColor) {
            texture = std::make_shared<Texture>(Texture::makeWhite());
        }
    };

    enum class Meshes {
        CUBE,
        SPHERE,
        CYLINDER,
        CAPSULE
    };

    enum class Materials {
        WHITE,
        BLACK,
        RED,
        GREY_BRICK
    };


    inline std::unordered_map<Materials, glm::vec4> colorVector = {
        {Materials::WHITE, {1.0f, 1.0f, 1.0f, 1.0f}},
        {Materials::BLACK, {0.0f, 0.0f, 0.0f, 1.0f}},
        {Materials::RED, {1.0f, 0.0f, 0.0f, 1.0f}},
    };

    inline std::unordered_map<Meshes, ShapeType> shape = {
        {Meshes::CUBE, ShapeType::Cube},
        {Meshes::SPHERE, ShapeType::Sphere},
        {Meshes::CYLINDER, ShapeType::Cylinder},
        {Meshes::CAPSULE, ShapeType::Capsule}
    };

    inline std::unordered_map<Materials, const char *> textureFile = {
        {Materials::GREY_BRICK, "grey-brick.jpg"}
    };

    class AssetManager {
    public:
        // I don't think this is necessary
        static AssetManager getInstance() {
            static AssetManager instance;
            return instance;
        }

        static std::shared_ptr<Material> getMaterial(const Materials name) {
            if (const auto it = m_material_cache.find(name); it != m_material_cache.end()) {
                return it->second;
            }
            std::shared_ptr<Material> newMaterial;
            switch (name) {
                case Materials::WHITE:
                case Materials::BLACK:
                case Materials::RED:
                    newMaterial = createColourMaterial(name);
                    break;
                case Materials::GREY_BRICK:
                    newMaterial = createTextureMaterial(name);
                    break;
            }

            // Create and cache the material if it doesn't exist
            m_material_cache[name] = newMaterial;
            return newMaterial;
        }

        static std::shared_ptr<Mesh> getMesh(const Meshes name) {
            if (const auto it = m_mesh_cache.find(name); it != m_mesh_cache.end()) {
                return it->second;
            }
            auto newMesh = std::make_shared<Mesh>(generateShape(shape[name]));

            // Create and cache the material if it doesn't exist
            m_mesh_cache[name] = newMesh;
            return newMesh;
        }

    private:
        AssetManager() = default;

        ~AssetManager() = default;

        static std::shared_ptr<Material> createTextureMaterial(const Materials name) {
            auto texture = TextureManager::loadTexture(textureFile[name]);
            return std::make_shared<Material>(texture);
        }

        static std::shared_ptr<Material> createColourMaterial(const Materials name) {
            return std::make_shared<Material>(colorVector[name]);
        }

        static std::unordered_map<Materials, std::shared_ptr<Material> > m_material_cache;
        static std::unordered_map<Meshes, std::shared_ptr<Mesh> > m_mesh_cache;
    };

    struct MeshInstance {
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
        Transform transform;

        MeshInstance(const Meshes meshType, const Materials materialType, const Transform &transformation = {})
            : transform(transformation) {
            mesh = AssetManager::getMesh(meshType);
            material = AssetManager::getMaterial(materialType);
        }
    };
}


#endif //OPENGLOBJVIEWER_ASSETMANAGER_H
