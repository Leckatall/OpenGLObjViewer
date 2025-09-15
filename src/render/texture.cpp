//
// Created by Lecka on 13/09/2025.
//

#include "texture.h"

#include <algorithm>
#include <cmath>

Texture::~Texture() {
    if (m_id) {
        // Ensure a valid GL context is current on this thread
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }
}

Texture::Texture(Texture &&other) noexcept {
    *this = std::move(other);
}

Texture &Texture::operator=(Texture &&other) noexcept {
    if (this != &other) {
        if (m_id)
            glDeleteTextures(1, &m_id);
        m_id = other.m_id;
        other.m_id = 0;
        m_width = other.m_width;
        other.m_width = 0;
        m_height = other.m_height;
        other.m_height = 0;
        m_internalFormat = other.m_internalFormat;
    }
    return *this;
}

GLenum Texture::chooseInternal(const bool srgb, const bool hasAlpha) {
    if (srgb) return hasAlpha ? GL_SRGB8_ALPHA8 : GL_SRGB8;
    return hasAlpha ? GL_RGBA8 : GL_RGB8;
}

void Texture::applyParams(const GLuint id, const TextureCreateInfo &desc) {
    // DSA: no bind required
    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, desc.minFilter);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, desc.magFilter);
    glTextureParameteri(id, GL_TEXTURE_WRAP_S, desc.wrapS);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, desc.wrapT);

#ifdef GL_TEXTURE_MAX_ANISOTROPY_EXT
    if (kDefaultAnisotropy > 1.0f) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, kDefaultAnisotropy);
    }
#endif
}

Texture Texture::fromPixels(const int w, const int h, const GLenum dataFormat, const GLenum dataType,
                            const void *pixels, const TextureCreateInfo &config) {
    Texture t;
    t.m_width = w;
    t.m_height = h;

    const bool hasAlpha = (dataFormat == GL_RGBA || dataFormat == GL_BGRA);
    t.m_internalFormat = chooseInternal(config.srgb, hasAlpha);

    glCreateTextures(GL_TEXTURE_2D, 1, &t.m_id);
    // Immutable storage with 1 mip level; we’ll generate more if requested
    const int levels = config.generateMipmaps ? (1 + static_cast<int>(std::floor(std::log2(std::max(w, h))))) : 1;
    glTextureStorage2D(t.m_id, levels, t.m_internalFormat, w, h);

    // Upload base level
    glTextureSubImage2D(t.m_id, 0, 0, 0, w, h, dataFormat, dataType, pixels);

    applyParams(t.m_id, config);

    if (config.generateMipmaps) {
        glGenerateTextureMipmap(t.m_id);
    }
    return t;
}

void Texture::bind(const GLuint unit) const {
    glBindTextureUnit(unit, m_id);
}

Texture Texture::makeWhite(const bool srgb) {
    constexpr unsigned char px[4] = {255, 255, 255, 255};
    TextureCreateInfo config;
    config.srgb = srgb;
    config.generateMipmaps = true;
    return fromPixels(1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px, config);
}

Texture Texture::fromFilePath(const std::filesystem::path &file_path, const TextureCreateInfo &config) {
    Texture texture{};
    glGenTextures(1, &texture.m_id);
    glBindTexture(GL_TEXTURE_2D, texture.m_id);

    applyParams(texture.m_id, config);

    int nrChannels;
    unsigned char *data = stbi_load(file_path.string().c_str(), &texture.m_width, &texture.m_height, &nrChannels, 0);
    if (data) {
        const GLint format = nrChannels == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, texture.m_width, texture.m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << file_path << std::endl;
        return makeWhite();
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}
