#pragma once
#include "main.hpp"
#include "Voxel.hpp"

class Voxel;

class World {
public:
    std::vector<Voxel> voxels;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
	std::vector<float> colors;
	std::vector<float> texCoords;
	//std::vector<std::vector<std::vector<Voxel*>>> _voxels;

    World(int numVoxels);
	// World(int sizeX, int sizeY, int sizeZ);
	// ~World();
	// void generate();
	// const Voxel&  getVoxel(int x, int y, int z) {
    //     return *_voxels[x][y][z];
    // }
   void generate(int numVoxels);
	private:
		int _sizeX;
		int _sizeY;
		int _sizeZ;
};