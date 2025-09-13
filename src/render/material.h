//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_MATERIAL_H
#define OPENGLOBJVIEWER_MATERIAL_H
#include <memory>

#include "texture.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"


class Material {
public:
    explicit Material(const glm::vec4 &color) : color(color), useTexture(false) {
    }

    explicit Material(const glm::vec3 &color) : Material(glm::vec4(color, 1.0f)) {
    }

    explicit Material(const std::shared_ptr<Texture> &texture)
        : texture(texture), color(glm::vec4(1.0f)), useTexture(true) {
    }

    [[nodiscard]] bool hasTexture() const { return useTexture; }
    [[nodiscard]] GLuint getTextureID() const { return texture ? texture->getID() : 0; }
    [[nodiscard]] glm::vec4 getColor() const { return color; }

private:
    std::shared_ptr<Texture> texture;
    glm::vec4 color;
    bool useTexture;
};


#endif //OPENGLOBJVIEWER_MATERIAL_H
