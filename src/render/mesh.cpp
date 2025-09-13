//
// Created by Lecka on 12/09/2025.
//

#include "mesh.h"


// void Mesh::Draw(const Shader &shader) const {
//     // bind appropriate textures
//     unsigned int diffuseNr = 1;
//     unsigned int specularNr = 1;
//     unsigned int normalNr = 1;
//     unsigned int heightNr = 1;
//     for (unsigned int i = 0; i < textures.size(); i++) {
//         glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
//         // retrieve texture number (the N in diffuse_textureN)
//         string number;
//         string name = textures[i].type;
//         if (name == "texture_diffuse")
//             number = to_string(diffuseNr++);
//         else if (name == "texture_specular")
//             number = to_string(specularNr++);
//         else if (name == "texture_normal")
//             number = to_string(normalNr++);
//         else if (name == "texture_height")
//             number = to_string(heightNr++);
//
//         // now set the sampler to the correct texture unit
//         glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
//         // and finally bind the texture
//         glBindTexture(GL_TEXTURE_2D, textures[i].id);
//     }
//
//     // draw mesh
//     glBindVertexArray(m_VAO);
//     glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
//     glBindVertexArray(0);
//
//     // always good practice to set everything back to defaults once configured.
//     glActiveTexture(GL_TEXTURE0);
// }

void Mesh::bind() const {
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 m_geometry.vertices.size() * sizeof(MeshGenerator::Vertex),
                 m_geometry.vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_geometry.indices.size() * sizeof(MeshGenerator::Vertex),
                 m_geometry.indices.data(),
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void *>(0));
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
}
