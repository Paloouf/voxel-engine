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

GLuint loadTexture(const char* path) {
    GLuint textureID = SOIL_load_OGL_texture(
        path,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        std::cerr << "Failed to load texture: " << SOIL_last_result() << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureID;
}

Renderer::Renderer(const World& world) : angle(0.0f) {
    vbo = new VertexBuffer(world.vertices.data(), world.vertices.size() * sizeof(float));
    ibo = new IndexBuffer(world.indices.data(), world.indices.size());
	cbo = new VertexBuffer(world.colors.data(), world.colors.size() * sizeof(float));
    tbo = new VertexBuffer(world.texCoords.data(), world.texCoords.size() * sizeof(float));
    programID = LoadShaders( "./srcs/shaders/vertexShader.glsl", "./srcs/shaders/fragShader.glsl" );
    textureID = loadTexture("./srcs/textures/image.png");
}

Renderer::~Renderer() {
    delete vbo;
    delete ibo;
	delete cbo;
}

void Renderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    glLoadIdentity();

//    gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,
//               0.0f, 0.0f, 0.0f,
//               0.0f, 1.0f, 0.0f);

// 	glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
//     glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);

// 	glTranslatef(cameraPositionX, cameraPositionY, 0.0f);
//     glScalef(zoomFactor, zoomFactor, zoomFactor);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(zoomFactor, zoomFactor, zoomFactor));

    glm::mat4 view = glm::lookAt(glm::vec3(cameraPositionX, cameraPositionY, cameraPositionZ),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

    GLint modelLoc = glGetUniformLocation(programID, "model");
    GLint viewLoc = glGetUniformLocation(programID, "view");
    GLint projLoc = glGetUniformLocation(programID, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindTexture(GL_TEXTURE_2D, textureID);

    ibo->Bind();
    vbo->Bind();
    glEnableVertexAttribArray(0); // Vertex positions
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glEnableVertexAttribArray(1); // Vertex colors
     tbo->Bind();
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    vbo->Unbind();
    tbo->Unbind();
    ibo->Unbind();

    //angle += 0.5f;

    glutSwapBuffers();
}
