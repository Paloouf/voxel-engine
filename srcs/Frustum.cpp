#include "../include/main.hpp"

// Frustum extractFrustum(const glm::mat4& viewProjMatrix) {
//     Frustum frustum;
//     const float* m = glm::value_ptr(viewProjMatrix);

//     // Left
//     frustum.planes[0] = glm::vec4(m[3] + m[0], m[7] + m[4], m[11] + m[8], m[15] + m[12]);
//     // Right
//     frustum.planes[1] = glm::vec4(m[3] - m[0], m[7] - m[4], m[11] - m[8], m[15] - m[12]);
//     // Bottom
//     frustum.planes[2] = glm::vec4(m[3] + m[1], m[7] + m[5], m[11] + m[9], m[15] + m[13]);
//     // Top
//     frustum.planes[3] = glm::vec4(m[3] - m[1], m[7] - m[5], m[11] - m[9], m[15] - m[13]);
//     // Near
//     frustum.planes[4] = glm::vec4(m[3] + m[2], m[7] + m[6], m[11] + m[10], m[15] + m[14]);
//     // Far
//     frustum.planes[5] = glm::vec4(m[3] - m[2], m[7] - m[6], m[11] - m[10], m[15] - m[14]);

//     // Normalize the planes
//     for (int i = 0; i < 6; i++) {
//         frustum.planes[i] /= glm::length(glm::vec3(frustum.planes[i]));
//     }

//     return frustum;
// }

Frustum extractFrustum(const glm::mat4& viewProjMatrix) {
    Frustum frustum;

    // Left plane
    frustum.planes[0] = glm::vec4(
        viewProjMatrix[0][3] + viewProjMatrix[0][0],
        viewProjMatrix[1][3] + viewProjMatrix[1][0],
        viewProjMatrix[2][3] + viewProjMatrix[2][0],
        viewProjMatrix[3][3] + viewProjMatrix[3][0]);

    // Right plane
    frustum.planes[1] = glm::vec4(
        viewProjMatrix[0][3] - viewProjMatrix[0][0],
        viewProjMatrix[1][3] - viewProjMatrix[1][0],
        viewProjMatrix[2][3] - viewProjMatrix[2][0],
        viewProjMatrix[3][3] - viewProjMatrix[3][0]);

    // Bottom plane
    frustum.planes[2] = glm::vec4(
        viewProjMatrix[0][3] + viewProjMatrix[0][1],
        viewProjMatrix[1][3] + viewProjMatrix[1][1],
        viewProjMatrix[2][3] + viewProjMatrix[2][1],
        viewProjMatrix[3][3] + viewProjMatrix[3][1]);

    // Top plane
    frustum.planes[3] = glm::vec4(
        viewProjMatrix[0][3] - viewProjMatrix[0][1],
        viewProjMatrix[1][3] - viewProjMatrix[1][1],
        viewProjMatrix[2][3] - viewProjMatrix[2][1],
        viewProjMatrix[3][3] - viewProjMatrix[3][1]);

    // Near plane
    frustum.planes[4] = glm::vec4(
        viewProjMatrix[0][3] + viewProjMatrix[0][2],
        viewProjMatrix[1][3] + viewProjMatrix[1][2],
        viewProjMatrix[2][3] + viewProjMatrix[2][2],
        viewProjMatrix[3][3] + viewProjMatrix[3][2]);

    // Far plane
    frustum.planes[5] = glm::vec4(
        viewProjMatrix[0][3] - viewProjMatrix[0][2],
        viewProjMatrix[1][3] - viewProjMatrix[1][2],
        viewProjMatrix[2][3] - viewProjMatrix[2][2],
        viewProjMatrix[3][3] - viewProjMatrix[3][2]);

    // Normalize the planes
    for (int i = 0; i < 6; i++) {
        float length = glm::length(glm::vec3(frustum.planes[i]));
        frustum.planes[i] /= length;
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

        // std::cout << "Plane["<< i << "]: " << plane.x << ", " << plane.y << ", " << plane.z << ", " << plane.w << std::endl;
        // std::cout << "Positive Vertex: " << positiveVertex.x << ", " << positiveVertex.y << ", " << positiveVertex.z << std::endl;
        // std::cout << "Dot Product + w: " << glm::dot(glm::vec3(plane), positiveVertex) + plane.w << std::endl;

        if (glm::dot(glm::vec3(plane), positiveVertex) + plane.w < 0) {//
            std::cout << "FALSE EVENT\n";
            return false;
        }
    }

    return true;
}

bool isVoxelOccluded(const Voxel& voxel, const glm::mat4& viewProjMatrix, GLuint depthFBO) {
    // Sample depth buffer at voxel's screen space coordinates
    glm::vec4 voxelPos = glm::vec4(voxel.x, voxel.y, voxel.z, 1.0f);
    glm::vec4 clipSpacePos = viewProjMatrix * voxelPos;
    glm::vec3 ndcPos = glm::vec3(clipSpacePos) / clipSpacePos.w;

    // Convert to window coordinates
    float winX = (ndcPos.x * 0.5f + 0.5f) * WIDTH;
    float winY = (ndcPos.y * 0.5f + 0.5f) * HEIGHT;

    // Read depth value from depth buffer
    float depthBufferValue;
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depthBufferValue);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Compare depth values
    float voxelDepth = ndcPos.z * 0.5f + 0.5f;
    return voxelDepth > depthBufferValue;
}