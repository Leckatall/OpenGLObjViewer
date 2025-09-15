//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_TEXTURE_MANAGER_H
#define OPENGLOBJVIEWER_TEXTURE_MANAGER_H


#include <filesystem>
#include <unordered_map>
#include <memory>

#include "texture.h"

const std::filesystem::path kTextureDir{"../assets/textures"};

namespace gfx::assets {
    class TextureManager {
    public:
        // Main entry
        static std::shared_ptr<Texture> loadTexture(std::filesystem::path filePath) {
            const std::string key = normalizePath(filePath);
            {
                std::lock_guard lock(mutex_);
                if (const auto it = m_cache.find(key); it != m_cache.end()) {
                    if (auto sp = it->second.lock()) return sp; // reuse existing
                }
            }
            auto texture = std::make_shared<Texture>(Texture::fromFilePath(filePath));
            {
                std::lock_guard lock(mutex_);
                m_cache[key] = texture;
            }
            return texture;
        }

        // Convenience overloads
        static std::shared_ptr<Texture> loadTexture(std::string_view path) {
            return loadTexture(kTextureDir / std::filesystem::path(path));
        }
        static std::shared_ptr<Texture> loadTexture(const char* path) {
            return loadTexture(kTextureDir / std::filesystem::path(path));
        }

    private:
        static std::string normalizePath(const std::filesystem::path& p) {
            // Avoid filesystem::canonical (requires a file to exist). Normalize separators to avoid dup keys.
            return p.lexically_normal().generic_string();
        }

        static inline std::unordered_map<std::string, std::weak_ptr<Texture>> m_cache;
        static inline std::mutex mutex_;
    };
}



#endif //OPENGLOBJVIEWER_TEXTURE_MANAGER_H