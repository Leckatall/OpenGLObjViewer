//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_RENDERER_H
#define OPENGLOBJVIEWER_RENDERER_H
#include <memory>
#include <vector>

#include "camera.h"
#include "camera_data.h"
#include "mesh.h"
#include "shader_program.h"
#include "glm/fwd.hpp"
#include "../Game/entity.h"



struct CameraUBOData {
    glm::mat4 uView;
    glm::mat4 uProj;
    glm::vec4 uCameraPosWS; // w component for padding
};

class Renderer {
public:
    Renderer();
    ~Renderer() = default;

    bool initialise();

    void setClearColor(const glm::vec4& color);

    void clear() const;

    void render(const std::vector<Mesh>& meshes);

    void renderEntity(const Entity& entity);


    void setLightPosition(const glm::vec3& lightPosition) { m_lightPosition = lightPosition; }

    void createCameraUBO() {
        glGenBuffers(1, &m_cameraUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, m_cameraUBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraUBOData), nullptr, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_cameraUBO);
    }

    void updateCameraUBO(const CameraData &camData) {
        const CameraUBOData uboData{camData.view, camData.proj, glm::vec4(camData.cameraPosWS, 1.0f)};

        if (m_cameraUBO == 0) createCameraUBO();

        glBindBuffer(GL_UNIFORM_BUFFER, m_cameraUBO);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraUBOData), &uboData);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

private:
    glm::vec4 m_clearColor;
    glm::vec3 m_lightPosition{0.0f, 2.0f, 0.0f};
    ShaderProgram m_shader;
    GLuint m_cameraUBO{};

    // // Internal helpers
    // void setupShaders();
    // void setupBuffers();
};


#endif //OPENGLOBJVIEWER_RENDERER_H