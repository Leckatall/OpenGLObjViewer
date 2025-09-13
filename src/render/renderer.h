//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_RENDERER_H
#define OPENGLOBJVIEWER_RENDERER_H
#include <memory>
#include <vector>

#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "glm/fwd.hpp"
#include "../Game/entity.h"

class Renderer {
public:
    Renderer();
    ~Renderer() = default;

    bool initialise();

    void setClearColor(const glm::vec4& color);

    void clear() const;

    void render(const std::vector<Mesh>& meshes);

    void renderEntity(const Entity& entity);

    void setViewProjectionMatrix(const glm::mat4& viewProjectionMatrix) {m_viewProjectionMatrix = viewProjectionMatrix;}

private:
    glm::vec4 m_clearColor;
    glm::mat4 m_viewProjectionMatrix{};
    glm::vec3 lightPos{0.0f, 2.0f, 0.0f};
    Shader* m_shader;

    // // Internal helpers
    // void setupShaders();
    // void setupBuffers();
};


#endif //OPENGLOBJVIEWER_RENDERER_H