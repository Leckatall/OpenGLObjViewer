//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_TEXTURE_H
#define OPENGLOBJVIEWER_TEXTURE_H

#include <filesystem>
#include <iostream>
#include <string>

#include "stb_image.h"
#include "glad/glad.h"



constexpr float kDefaultAnisotropy = 8.0f; // set to 1.0f to “disable”

struct TextureCreateInfo {
    // Defaults that work for most color textures
    GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR;
    GLenum magFilter = GL_LINEAR;
    GLenum wrapS = GL_REPEAT;
    GLenum wrapT = GL_REPEAT;
    bool srgb = true;          // GL_SRGB8_ALPHA8 for color textures
    float anisotropy = kDefaultAnisotropy;   // clamped to device max if supported
    bool generateMipmaps = true;
};

class Texture {
public:
    Texture() = default;
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    // Create from pixel memory (RGBA8-style inputs commonly)
    static Texture fromPixels(int width, int height,
                              GLenum dataFormat, GLenum dataType,
                              const void* pixels, const TextureCreateInfo& desc = {});

    // TODO: Handle files in a dedicated class
    static Texture fromFilePath(const std::filesystem::path& file_path, const TextureCreateInfo& config = {});

    static Texture fromFileName(const std::string& file_name, const TextureCreateInfo& config = {});

    // Bind helper (unit = texture unit index)
    void bind(GLuint unit = 0) const;

    // Metadata
    [[nodiscard]] GLuint id() const { return m_id; }
    [[nodiscard]] int width() const { return m_width; }
    [[nodiscard]] int height() const { return m_height; }
    [[nodiscard]] GLenum internalFormat() const { return m_internalFormat; }

    // Make a 1x1 white texture (useful as default)
    static Texture makeWhite(bool srgb = true);

private:
    static void applyParams(GLuint id, const TextureCreateInfo& desc);
    static GLenum chooseInternal(bool srgb, bool hasAlpha);

    GLuint m_id = 0;
    int m_width = 0;
    int m_height = 0;
    GLenum m_internalFormat = GL_RGBA8;
};



#endif //OPENGLOBJVIEWER_TEXTURE_H