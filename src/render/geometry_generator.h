//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_GEOMETRY_GENERATOR_H
#define OPENGLOBJVIEWER_GEOMETRY_GENERATOR_H
#include <vector>
#include <cmath>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#define SCF(x) static_cast<float>(x)


namespace MeshGenerator {
    constexpr float M_PI_F = 3.14159265358979323846f;
    constexpr float RADIUS = 0.5f;
    constexpr float HEIGHT = 1.0f;

    struct Vertex {
        glm::vec3 position; // Position
        glm::vec3 normal; // Normal vector
        glm::vec2 uv; // UV coordinates
    };

    struct MeshData {
        std::vector<Vertex> vertices; // Vertex positions, normals, texture coords
        std::vector<unsigned int> indices; // Indices for EBO rendering
    };

    enum class ShapeType {
        Cube,
        Sphere,
        Cylinder,
        Capsule
    };


    inline MeshData generateCube() {
        MeshData mesh;

        mesh.vertices = {
            // Front face
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            // Back face
            {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

            // Left face
            {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Right face
            {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Top face
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

            // Bottom face
            {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        };

        // Indices for triangles (using EBO)
        mesh.indices = {
            // Front face
            0, 1, 2, 0, 2, 3,
            // Back face
            4, 5, 6, 4, 6, 7,
            // Left face
            8, 9, 10, 8, 10, 11,
            // Right face
            12, 13, 14, 12, 14, 15,
            // Top face
            16, 17, 18, 16, 18, 19,
            // Bottom face
            20, 21, 22, 20, 22, 23
        };

        return mesh;
    }

    inline MeshData generateSphere(const int res) {
        MeshData mesh;

        // Sphere generation using latitude-longitude (UV Sphere)
        for (int lat = 0; lat <= res; ++lat) {
            const float theta = SCF(lat) * M_PI_F / SCF(res);
            // theta is the longitude angle at which to place the vertex
            const float sinTheta = sinf(theta);
            const float cosTheta = cosf(theta);

            for (int lon = 0; lon <= res; ++lon) {
                const float phi = SCF(lon) * 2 * M_PI_F / SCF(res);
                // phi is the longitude angle at which to place the vertex

                // Vertex positions
                const float x = RADIUS * cosf(phi) * sinTheta;
                const float y = RADIUS * cosTheta;
                const float z = RADIUS * sinf(phi) * sinTheta;

                // UV coordinates
                const float u = SCF(lon) / SCF(res);
                const float v = SCF(lat) / SCF(res);

                // Normal vectors (unit vector pointing outward)
                const float nx = cosf(phi) * sinTheta;
                const float ny = cosTheta;
                const float nz = sinf(phi) * sinTheta;


                mesh.vertices.push_back({{x, y, z}, {nx, ny, nz}, {u, v}});
            }
        }
        return mesh;
    }

    inline MeshData generateCylinder(const int res) {
        MeshData mesh;

        // Generate top and bottom circle vertices
        for (int i = 0; i <= res; ++i) {
            const float theta = SCF(i) * 2 * M_PI_F / SCF(res);
            const float x = RADIUS * cosf(theta);
            const float z = RADIUS * sinf(theta);

            // Top circle
            mesh.vertices.push_back({{x, HEIGHT / 2, z}, {0.0f, 1.0f, 0.0f}, {SCF(i) / SCF(res), 1.0f}});

            // Bottom circle
            mesh.vertices.push_back({{x, -HEIGHT / 2, z}, {0.0f, -1.0f, 0.0f}, {SCF(i) / SCF(res), 0.0f}});
        }

        // Generate indices for the top and bottom faces
        for (int i = 0; i < res; ++i) {
            // Top face
            mesh.indices.push_back(0);
            mesh.indices.push_back(i + 1);
            mesh.indices.push_back(i + 2);

            // Bottom face
            const int base = res + 1;
            mesh.indices.push_back(base);
            mesh.indices.push_back(base + i + 2);
            mesh.indices.push_back(base + i + 1);
        }

        // Generate indices for the side faces
        for (int i = 0; i < res; ++i) {
            const int topCurrent = i + 1;
            const int topNext = (i + 1) % res + 1;
            const int bottomCurrent = res + 1 + i + 1;
            const int bottomNext = res + 1 + (i + 1) % res + 1;

            // First triangle
            mesh.indices.push_back(topCurrent);
            mesh.indices.push_back(bottomCurrent);
            mesh.indices.push_back(topNext);

            // Second triangle
            mesh.indices.push_back(topNext);
            mesh.indices.push_back(bottomCurrent);
            mesh.indices.push_back(bottomNext);
        }

        return mesh;
    }

    inline MeshData generateCapsule(const int res) {
        MeshData mesh;
        constexpr float cylinderHeight = HEIGHT - (2 * RADIUS); // Height of the cylinder body
        const int stacks = res / 2; // Number of stacks for the hemispheres

        // Generate hemispheres (top and bottom) in a single loop
        for (int i = 0; i <= stacks; ++i) {
            const float phi = M_PI_F * SCF(i) / SCF(stacks); // Latitude angle
            for (int j = 0; j <= res; ++j) {
                const float theta = 2.0f * M_PI_F * SCF(j) / SCF(res); // Longitude angle
                const float x = RADIUS * sinf(phi) * cosf(theta);
                const float z = RADIUS * sinf(phi) * sinf(theta);

                const float nx = sinf(phi) * cosf(theta);
                const float ny = cosf(phi);
                const float nz = sinf(phi) * sinf(theta);

                // Bottom hemisphere
                const float yBottom = -cylinderHeight / 2 - RADIUS * cosf(phi);
                const float vBottom = SCF(i) / SCF(stacks); // UV mapping for v
                const float u = SCF(j) / SCF(res);
                mesh.vertices.push_back({{x, yBottom, z}, {nx, -ny, nz}, {u, vBottom}});

                // Top hemisphere
                const float yTop = cylinderHeight / 2 + RADIUS * cosf(phi);
                const float vTop = 1.0f - vBottom;
                mesh.vertices.push_back({{x, yTop, z}, {nx, ny, nz}, {u, vTop}});
            }
        }

        // Generate the cylinder body
        for (int i = 0; i <= res; ++i) {
            const float theta = 2.0f * M_PI_F * SCF(i) / SCF(res);
            const float x = RADIUS * cosf(theta);
            const float z = RADIUS * sinf(theta);

            const float nx = cosf(theta); // Normal for the sides
            const float nz = sinf(theta);

            const float u = SCF(i) / SCF(res);
            mesh.vertices.push_back({{x, -cylinderHeight / 2, z}, {nx, 0.0f, nz}, {u, 0.0f}}); // Bottom edge
            mesh.vertices.push_back({{x, cylinderHeight / 2, z}, {nx, 0.0f, nz}, {u, 1.0f}}); // Top edge
        }

        // Indices generation remains unchanged
        // Bottom hemisphere indices
        int baseIndex = 0;
        for (int i = 0; i < stacks; ++i) {
            for (int j = 0; j < res; ++j) {
                const int current = baseIndex + i * (res + 1) + j;
                const int next = current + res + 1;

                mesh.indices.push_back(current);
                mesh.indices.push_back(next);
                mesh.indices.push_back(current + 1);

                mesh.indices.push_back(current + 1);
                mesh.indices.push_back(next);
                mesh.indices.push_back(next + 1);
            }
        }

        // Cylinder side indices
        baseIndex = stacks * (res + 1);
        for (int i = 0; i < res; ++i) {
            const int bottom1 = baseIndex + i * 2;
            const int top1 = bottom1 + 1;
            const int bottom2 = baseIndex + (i + 1) * 2;
            const int top2 = bottom2 + 1;

            mesh.indices.push_back(bottom1);
            mesh.indices.push_back(top1);
            mesh.indices.push_back(bottom2);

            mesh.indices.push_back(top1);
            mesh.indices.push_back(top2);
            mesh.indices.push_back(bottom2);
        }
        return mesh;
    }

    inline MeshData generateShape(const ShapeType type, const int res = 20) {
        switch (type) {
            case ShapeType::Cube:
                return generateCube();
            case ShapeType::Sphere:
                return generateSphere(res);
            case ShapeType::Cylinder:
                return generateCylinder(res);
            case ShapeType::Capsule:
                return generateCapsule(res);
        }
        return {};
    }
}


#endif //OPENGLOBJVIEWER_GEOMETRY_GENERATOR_H
