//
// Created by Lecka on 13/09/2025.
//

#include "renderer.h"

#include "GLFW/glfw3.h"

Renderer::Renderer() : m_clearColor(0.2f, 0.3f, 0.3f, 1.0f), m_shader("basic_lighting") {
}

bool Renderer::initialise() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    return true;
}

void Renderer::setClearColor(const glm::vec4 &color) {
    m_clearColor = color;
}

void Renderer::clear() const {
    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const std::vector<Mesh>& meshes) {
    // for (const auto& mesh : meshes) {
    //     // Bind the mesh's shader
    //     mesh.shader.use();
    //
    //     // Set uniform for the view-projection matrix
    //     mesh.shader.setMat4("u_ViewProjection", viewProjectionMatrix);
    //
    //     // Bind the mesh's vertex array
    //     glBindVertexArray(mesh.vao);
    //
    //     // Draw the mesh
    //     glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
    //
    //     // Unbind the vertex array
    //     glBindVertexArray(0);
    // }
}

void Renderer::renderEntity(const Entity &entity) {
    // Bind the shader (assumes you're using the same shader for all entities here)
    m_shader.use();

    // Calculate the final model-view-projection matrix
    const glm::mat4 modelMatrix = entity.getMatrix();
    //const glm::mat4 mvpMatrix = m_viewProjectionMatrix * glm::translate(glm::mat4(1.0f), entity.getPosition()) * modelMatrix;
    // Set shader uniforms
    m_shader.setMat4("model", modelMatrix);
    m_shader.setVec3("lightPos", m_lightPosition);
    m_shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    m_shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    // Render the mesh
    const auto& mesh = entity.getMesh();
    mesh->bind();
    glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
}
