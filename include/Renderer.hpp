#pragma once
#include "main.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Voxel.hpp"
#include "World.hpp"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class IndexBuffer;
class VertexBuffer;
class Voxel;
class World;

class Renderer {
	private:
		VertexBuffer* vbo;
		IndexBuffer* ibo;
		VertexBuffer* cbo;
		float angle;

	public:
		Renderer(const World& world);
		~Renderer();
		void draw();
		void setCameraPosition(float x, float y, float z);
		void setRotationAngle(float angleX, float angleY);
		void setZoomFactor(float zoom);
		
		float rotationAngleX;
		float rotationAngleY;
		float sensitivity = 1.0f;
		float cameraPositionX;
		float cameraPositionY;
		float cameraPositionZ = 100.0f;
		float panSpeed = 1.0f;
		float zoomFactor = 1.0f;
		float zoomSpeed = 1.0f;
		float minZoom = 1.0f;
		float maxZoom = 100.f;
		float moveSpeed = 5.0f;
};