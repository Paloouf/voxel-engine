#pragma once
#include "main.hpp"

struct Frustum {
    glm::vec4 planes[6];
};

Frustum extractFrustum(const glm::mat4& viewProjMatrix);
bool isVoxelInFrustum(const Voxel& voxel, const Frustum& frustum);
bool isVoxelOccluded(const Voxel& voxel, const glm::mat4& viewProjMatrix, GLuint depthFBO);