#include "../include/World.hpp"

World::World(int numVoxels) {
    generate(numVoxels);
}

// World::World(int sizeX, int sizeY, int sizeZ) : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ) {
// 	_voxels.resize(sizeX);
// 	for(int x = 0; x < sizeX; x++)
// 	{
// 		_voxels[x].resize(sizeY);
// 		for(int y = 0; y < sizeY; y++)
// 		{
// 			_voxels[x][y].resize(sizeZ);
// 			for (int z = 0; z < sizeZ; z++)
// 			{
// 				std::cout << x << y <<z << std::endl;
// 				_voxels[x][y][z] = new Voxel(x * 2.0f,y * 2.0f,z * 2.0f);
// 			}
// 		}
// 	}
// 	generate();
// }

// void World::generate() {
// 	for(int x = 0; x < _sizeX; x++)
// 	{
// 		for(int y = 0; y < _sizeY; y++)
// 		{
// 			for (int z = 0; z < _sizeZ; z++)
// 			{
// 				unsigned int baseIndex = vertices.size() / 3;
// 				vertices.insert(vertices.end(), _voxels[x][y][z]->vertices.begin(), _voxels[x][y][z]->vertices.end());
// 				colors.insert(colors.end(), _voxels[x][y][z]->colors.begin(), _voxels[x][y][z]->colors.end());
// 				for (unsigned int index : _voxels[x][y][z]->indices) {
// 					indices.push_back(baseIndex + index);
// 				}
// 			}
// 		}
// 	}
// 	for (std::vector<float>::iterator i = vertices.begin(); i != vertices.end(); i++)
// 		std::cout << *i << std::endl;
// }

// World::~World(){
// 	for (int x = 0; x < _sizeX; x++){
// 		for (int y = 0; y < _sizeY; y++){
// 			for (int z = 0; z < _sizeZ; z++){
// 				delete _voxels[x][y][z];
// 			}
// 		}
// 	}
// }
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
        unsigned int baseIndex = vertices.size() / 3;
        vertices.insert(vertices.end(), voxel.vertices.begin(), voxel.vertices.end());
		colors.insert(colors.end(), voxel.colors.begin(), voxel.colors.end());
        for (unsigned int index : voxel.indices) {
            indices.push_back(baseIndex + index);
        }
    }
	// for (std::vector<float>::iterator i = vertices.begin(); i != vertices.end(); i++)
 	// 	std::cout << *i << std::endl;
}