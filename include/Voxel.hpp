#pragma once

#include "main.hpp"

enum VoxType {
	BlockType_Default = 0,
	BlockType_Grass,
	BlockType_Dirt,
	BlockType_Water,
	BlockType_Stone,
	BlockType_Wood,
	BlockType_Sand,
	BlockType_NumTypes,
};

class Voxel{
	public:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		std::vector<float> colors;
		std::vector<float> texCoords;
		float x, y, z;

		Voxel(float x, float y, float z);
		~Voxel();
		bool isActive() const;
		void setActive(bool active);
	private:
		bool m_active;
		VoxType m_voxType;
};

