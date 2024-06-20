#pragma once
#include "main.hpp"
#include "Voxel.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Voxel;

class World {
	public:
		std::vector<Voxel> voxels;
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		std::vector<float> colors;
		std::vector<float> texCoords;
		int numVoxels;

		World(int numVoxels);
		void generate(int numVoxels);
		void updateVisibility(const glm::mat4& viewProjMatrix);
	private:
		int _sizeX;
		int _sizeY;
		int _sizeZ;
};