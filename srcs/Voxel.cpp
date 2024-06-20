#include "../include/Voxel.hpp"

Voxel::Voxel(float x, float y, float z) : x(x), y(y), z(z) {
    // Define vertices relative to the voxel position
    vertices = {
        // Front face
        x - 1.0f, y - 1.0f, z + 1.0f,
        x + 1.0f, y - 1.0f, z + 1.0f,
        x + 1.0f, y + 1.0f, z + 1.0f,
        x - 1.0f, y + 1.0f, z + 1.0f,
        // Back face
        x - 1.0f, y - 1.0f, z - 1.0f,
        x + 1.0f, y - 1.0f, z - 1.0f,
        x + 1.0f, y + 1.0f, z - 1.0f,
        x - 1.0f, y + 1.0f, z - 1.0f,
        // Left face
        x - 1.0f, y - 1.0f, z - 1.0f,
        x - 1.0f, y - 1.0f, z + 1.0f,
        x - 1.0f, y + 1.0f, z + 1.0f,
        x - 1.0f, y + 1.0f, z - 1.0f,
        // Right face
        x + 1.0f, y - 1.0f, z - 1.0f,
        x + 1.0f, y - 1.0f, z + 1.0f,
        x + 1.0f, y + 1.0f, z + 1.0f,
        x + 1.0f, y + 1.0f, z - 1.0f,
        // Top face
        x - 1.0f, y + 1.0f, z + 1.0f,
        x + 1.0f, y + 1.0f, z + 1.0f,
        x + 1.0f, y + 1.0f, z - 1.0f,
        x - 1.0f, y + 1.0f, z - 1.0f,
        // Bottom face
        x - 1.0f, y - 1.0f, z + 1.0f,
        x + 1.0f, y - 1.0f, z + 1.0f,
        x + 1.0f, y - 1.0f, z - 1.0f,
        x - 1.0f, y - 1.0f, z - 1.0f,
    };
    // Define indices
    indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Top face
        16, 17, 18, 18, 19, 16,
        // Bottom face
        20, 21, 22, 22, 23, 20,
    };

	colors = {
        1.0f, 0.0f, 0.0f, 1.0f, // Red
        0.0f, 1.0f, 0.0f, 1.0f, // Green
         0.0f, 0.0f, 1.0f, 1.0f, // Blue
         1.0f, 1.0f, 0.0f, 1.0f, // Yellow
         1.0f, 0.0f, 1.0f, 1.0f, // Magenta
         0.0f, 1.0f, 1.0f, 1.0f, // Cyan
         1.0f, 0.5f, 0.0f, 1.0f, // Orange
         0.5f, 0.0f, 0.5f, 1.0f, // Purple
    };

    texCoords = {
        // Front face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Back face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Left face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Right face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Top face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Bottom face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };
}

Voxel::~Voxel() {}

bool Voxel::isActive() const { return m_active; }

void Voxel::setActive(bool active) {
	m_active = active;
}
