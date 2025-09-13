//
// Created by Lecka on 12/09/2025.
//

#ifndef OPENGLOBJVIEWER_MESH_H
#define OPENGLOBJVIEWER_MESH_H


#include "geometry_generator.h"
#include "material.h"

class Mesh {
public:
    explicit Mesh(const MeshGenerator::Geometry &geometry, const std::shared_ptr<Material> &material)
        : m_geometry(geometry),
          m_material(material) {
        setupMesh();
    }

    void bind() const;

    size_t getIndexCount() const { return m_geometry.indices.size(); }

private:
    MeshGenerator::Geometry m_geometry;
    std::shared_ptr<Material> m_material;
    unsigned int m_VAO, m_VBO, m_EBO;

    void setupMesh();
};

#endif //OPENGLOBJVIEWER_MESH_H
