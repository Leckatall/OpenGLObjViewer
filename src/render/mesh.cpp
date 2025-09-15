//
// Created by Lecka on 12/09/2025.
//

#include "mesh.h"

#include "glad/glad.h"

void Mesh::bind() const {
    glBindVertexArray(m_VAO);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 m_geometry.vertices.size() * sizeof(gfx::Vertex),
                 m_geometry.vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_geometry.indices.size() * sizeof(gfx::Index),
                 m_geometry.indices.data(),
                 GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(gfx::Vertex),
                          reinterpret_cast<void *>(offsetof(gfx::Vertex, position)));

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(gfx::Vertex),
                          reinterpret_cast<void *>(offsetof(gfx::Vertex, normal)));

    // UV
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          sizeof(gfx::Vertex),
                          reinterpret_cast<void *>(offsetof(gfx::Vertex, uv)));

    glBindVertexArray(0); // optional but helps avoid accidental edits
}
