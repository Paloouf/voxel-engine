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
    };

    // Define indices
    indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        0, 4, 7, 7, 3, 0,
        // Right face
        1, 5, 6, 6, 2, 1,
        // Top face
        3, 2, 6, 6, 7, 3,
        // Bottom face
        0, 1, 5, 5, 4, 0
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
}

Voxel::~Voxel() {}

bool Voxel::isActive() { return m_active; }

void Voxel::setActive(bool active) {
	m_active = active;
}
