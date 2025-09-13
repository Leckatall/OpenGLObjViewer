//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_TEXTURE_H
#define OPENGLOBJVIEWER_TEXTURE_H

#include <iostream>
#include <string>

#include "stb_image.h"
#include "glad/glad.h"

constexpr auto TEXTURE_DIR = "../assets/textures/";

class Texture {
public:
    explicit Texture(const char& fileName);

    [[nodiscard]] GLuint getID() const { return textureId; }

    ~Texture() { glDeleteTextures(1, &textureId); }

private:
    GLuint textureId{};

    static void setWrappingParameters();

    static void setFilteringParameters();
};



#endif //OPENGLOBJVIEWER_TEXTURE_H