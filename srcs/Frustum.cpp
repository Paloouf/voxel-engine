#include "../include/main.hpp"

Frustum extractFrustum(const glm::mat4& viewProjMatrix) {
    Frustum frustum;
    const float* m = glm::value_ptr(viewProjMatrix);

    // Left
    frustum.planes[0] = glm::vec4(m[3] + m[0], m[7] + m[4], m[11] + m[8], m[15] + m[12]);
    // Right
    frustum.planes[1] = glm::vec4(m[3] - m[0], m[7] - m[4], m[11] - m[8], m[15] - m[12]);
    // Bottom
    frustum.planes[2] = glm::vec4(m[3] + m[1], m[7] + m[5], m[11] + m[9], m[15] + m[13]);
    // Top
    frustum.planes[3] = glm::vec4(m[3] - m[1], m[7] - m[5], m[11] - m[9], m[15] - m[13]);
    // Near
    frustum.planes[4] = glm::vec4(m[3] + m[2], m[7] + m[6], m[11] + m[10], m[15] + m[14]);
    // Far
    frustum.planes[5] = glm::vec4(m[3] - m[2], m[7] - m[6], m[11] - m[10], m[15] - m[14]);

    // Normalize the planes
    for (int i = 0; i < 6; i++) {
        frustum.planes[i] /= glm::length(glm::vec3(frustum.planes[i]));
    }

    return frustum;
}

bool isVoxelInFrustum(const Voxel& voxel, const Frustum& frustum) {
    glm::vec3 min = glm::vec3(voxel.x - 1.0f, voxel.y - 1.0f, voxel.z - 1.0f);
    glm::vec3 max = glm::vec3(voxel.x + 1.0f, voxel.y + 1.0f, voxel.z + 1.0f);

    for (int i = 0; i < 6; i++) {
        glm::vec4 plane = frustum.planes[i];
        glm::vec3 positiveVertex = glm::vec3(
            plane.x < 0 ? min.x : max.x,
            plane.y < 0 ? min.y : max.y,
            plane.z < 0 ? min.z : max.z
        );

        if (glm::dot(glm::vec3(plane), positiveVertex) + plane.w < 0) {//
            return false;
        }
    }

    return true;
}