#include "../include/Renderer.hpp"

void GLClearError(){
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line){
	(void)line;
	while (GLenum error = glGetError()){
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << std::endl;
		return false;
	}
	return true;
}

Renderer::Renderer(const World& world) : angle(0.0f) {
    vbo = new VertexBuffer(world.vertices.data(), world.vertices.size() * sizeof(float));
    ibo = new IndexBuffer(world.indices.data(), world.indices.size());
	cbo = new VertexBuffer(world.colors.data(), world.colors.size() * sizeof(float));
}

Renderer::~Renderer() {
    delete vbo;
    delete ibo;
	delete cbo;
}

void Renderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

   gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

	glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);

	glTranslatef(cameraPositionX, cameraPositionY, 0.0f);
    glScalef(zoomFactor, zoomFactor, zoomFactor);

    vbo->Bind();
	//cbo->Bind();
    ibo->Bind();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // glEnableVertexAttribArray(0); // Vertex positions
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(unsigned int), (void*)0);


	// glEnableClientState(GL_COLOR_ARRAY);
    // glColorPointer(4, GL_FLOAT, 0, 0);

    // glEnableVertexAttribArray(1); // Vertex colors
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(unsigned int), (void*)0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);

	glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);

    vbo->Unbind();
	//cbo->Unbind();
    ibo->Unbind();

    //angle += 0.5f;

    glutSwapBuffers();
}
