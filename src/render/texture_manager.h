//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_TEXTURE_MANAGER_H
#define OPENGLOBJVIEWER_TEXTURE_MANAGER_H


#include <unordered_map>
#include <memory>

#include "texture.h"


class TextureManager {
public:
    static std::shared_ptr<Texture> loadTexture(const char& filePath) {
        if (auto it = textureCache.find(filePath); it != textureCache.end()) {
            return it->second;
        }
        auto texture = std::make_shared<Texture>(filePath);
        textureCache[filePath] = texture;
        return texture;
    }

private:
    static inline std::unordered_map<char, std::shared_ptr<Texture>> textureCache;
};


#endif //OPENGLOBJVIEWER_TEXTURE_MANAGER_H