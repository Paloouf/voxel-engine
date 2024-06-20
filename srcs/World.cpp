#include "../include/main.hpp"

World::World(int numVoxels) :numVoxels(numVoxels) {
    generate(numVoxels);
}

void World::generate(int numVoxels) {
    int numVoxelsPerDimension = numVoxels;

    for (int x = 0; x < numVoxelsPerDimension; ++x) {
        for (int y = 0; y < numVoxelsPerDimension; ++y) {
            for (int z = 0; z < numVoxelsPerDimension; ++z) {
                voxels.emplace_back(x * 2.0f, y * 2.0f, z * 2.0f);
            }
        }
    }
    for (const Voxel& voxel : voxels) {
        if (voxel.isActive()){
            unsigned int baseIndex = vertices.size() / 3;
            vertices.insert(vertices.end(), voxel.vertices.begin(), voxel.vertices.end());
            colors.insert(colors.end(), voxel.colors.begin(), voxel.colors.end());
            texCoords.insert(texCoords.end(), voxel.texCoords.begin(), voxel.texCoords.end());
            for (unsigned int index : voxel.indices) {
                indices.push_back(baseIndex + index);
            }
        }
    }
	// for (std::vector<float>::iterator i = vertices.begin(); i != vertices.end(); i++)
 	// 	std::cout << *i << std::endl;
}

void World::updateVisibility(const glm::mat4& viewProjMatrix) {
    Frustum frustum = extractFrustum(viewProjMatrix);
    for (std::vector<Voxel>::iterator it = voxels.begin(); it != voxels.end(); it++){
        (*it).setActive(isVoxelInFrustum((*it), frustum));
    }
}