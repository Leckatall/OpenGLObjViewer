//
// Created by Lecka on 12/09/2025.
//

#ifndef OPENGLOBJVIEWER_MESH_H
#define OPENGLOBJVIEWER_MESH_H


#include <utility>

#include "geometry_generator.h"

class Mesh {
public:
    explicit Mesh(gfx::Geometry geometry)
        : m_geometry(std::move(geometry)) {
        setupMesh();
    }

    void bind() const;

    [[nodiscard]] size_t getIndexCount() const { return m_geometry.indices.size(); }

private:
    gfx::Geometry m_geometry;
    unsigned int m_VAO{}, m_VBO{}, m_EBO{};

    void setupMesh();
};

#endif //OPENGLOBJVIEWER_MESH_H
