#pragma once
#include "main.hpp"
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


class Renderer {
	private:
		VertexBuffer* vbo;
		IndexBuffer* ibo;
		VertexBuffer* cbo;
		VertexBuffer* tbo;
		//FrameBuffer* fbo;
		float angle;
		World* world;

	public:
		Renderer(World* world);
		~Renderer();
		void draw();
		void updateVBO();
		void drawFrustum(const glm::mat4& invViewProj);
		void moveCamera(float deltaX, float deltaY, float deltaZ);
		void updateViewMatrix();
		void initializeDepthResources();
		void renderSceneToDepthBuffer();
		void renderDepthBuffer();
		// void setCameraPosition(float x, float y, float z);
		// void setRotationAngle(float angleX, float angleY);
		// void setZoomFactor(float zoom);

		GLuint programID;
		GLuint depthProgramID;
		GLuint textureID;
		GLuint depthFBO;
		GLuint depthTexture;
		
		glm::vec3 cameraPosition;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjMatrix;
		glm::mat4 view;
		glm::mat4 projection;
		double lastTime;
 		int nbFrames = 0;
		float rotationAngleX;
		float rotationAngleY;
		float sensitivity = 1.0f;
		float cameraPositionX = 0.0f;
		float cameraPositionY = 0.0f;
		float cameraPositionZ = 100.0f;
		float panSpeed = 1.0f;
		float zoomFactor = 1.0f;
		float zoomSpeed = 1.0f;
		float minZoom = 1.0f;
		float maxZoom = 100.f;
		float moveSpeed = 5.0f;
};