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

std::array<glm::vec3, 8> calculateFrustumCorners(const glm::mat4& invViewProj) {
    std::array<glm::vec3, 8> corners;
    std::array<glm::vec4, 8> ndcCorners = {
        glm::vec4(-1, -1, -1, 1), glm::vec4(1, -1, -1, 1),
        glm::vec4(1, 1, -1, 1), glm::vec4(-1, 1, -1, 1),
        glm::vec4(-1, -1, 1, 1), glm::vec4(1, -1, 1, 1),
        glm::vec4(1, 1, 1, 1), glm::vec4(-1, 1, 1, 1)
    };
    
    for (int i = 0; i < 8; ++i) {
        glm::vec4 worldPos = invViewProj * ndcCorners[i];
        worldPos /= worldPos.w;
        corners[i] = glm::vec3(worldPos);
    }
    
    return corners;
}

Renderer::Renderer(World* world) : world(world) 
{
    vbo = new VertexBuffer(world->vertices.data(), world->vertices.size() * sizeof(float));
    ibo = new IndexBuffer(world->indices.data(), world->indices.size());
	cbo = new VertexBuffer(world->colors.data(), world->colors.size() * sizeof(float));
    tbo = new VertexBuffer(world->texCoords.data(), world->texCoords.size() * sizeof(float));
    programID = LoadShaders( "./srcs/shaders/vertexShader.glsl", "./srcs/shaders/fragShader.glsl" );
    depthProgramID = LoadShaders("./srcs/shaders/depthVertex.glsl", "./srcs/shaders/depthFragment.glsl");
    textureID = loadTexture("./srcs/textures/image.png");
    cameraPosition = glm::vec3(cameraPositionX, cameraPositionY, cameraPositionZ);
    projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 1000.0f);
    view = glm::lookAt(
        glm::vec3(cameraPositionX, cameraPositionY, cameraPositionZ),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    viewMatrix = projection * view;
    viewProjMatrix = projection * viewMatrix;
}

Renderer::~Renderer() {
    delete vbo;
    delete ibo;
	delete cbo;
}

void Renderer::drawFrustum(const glm::mat4& invViewProj) {
    std::array<glm::vec3, 8> corners = calculateFrustumCorners(invViewProj);
    std::cout << "frustum drawing\n";
    glBegin(GL_LINES);
    // Near plane
    glVertex3fv(glm::value_ptr(corners[0]));
    glVertex3fv(glm::value_ptr(corners[1]));

    glVertex3fv(glm::value_ptr(corners[1]));
    glVertex3fv(glm::value_ptr(corners[2]));

    glVertex3fv(glm::value_ptr(corners[2]));
    glVertex3fv(glm::value_ptr(corners[3]));

    glVertex3fv(glm::value_ptr(corners[3]));
    glVertex3fv(glm::value_ptr(corners[0]));

    // Far plane
    glVertex3fv(glm::value_ptr(corners[4]));
    glVertex3fv(glm::value_ptr(corners[5]));

    glVertex3fv(glm::value_ptr(corners[5]));
    glVertex3fv(glm::value_ptr(corners[6]));

    glVertex3fv(glm::value_ptr(corners[6]));
    glVertex3fv(glm::value_ptr(corners[7]));

    glVertex3fv(glm::value_ptr(corners[7]));
    glVertex3fv(glm::value_ptr(corners[4]));

    // Connecting lines
    glVertex3fv(glm::value_ptr(corners[0]));
    glVertex3fv(glm::value_ptr(corners[4]));

    glVertex3fv(glm::value_ptr(corners[1]));
    glVertex3fv(glm::value_ptr(corners[5]));

    glVertex3fv(glm::value_ptr(corners[2]));
    glVertex3fv(glm::value_ptr(corners[6]));

    glVertex3fv(glm::value_ptr(corners[3]));
    glVertex3fv(glm::value_ptr(corners[7]));
    glEnd();
}

void Renderer::moveCamera(float deltaX, float deltaY, float deltaZ) {
    std::cout << "WOMP WOMP\n";
    cameraPosition += glm::vec3(deltaX, deltaY, deltaZ);
    std::cout << cameraPosition.x << cameraPosition.y << cameraPosition.z << std::endl;
    updateViewMatrix();
}

void Renderer::updateViewMatrix() {
    //glm::mat4 projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 1000.0f);
    viewMatrix = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::draw() {
    renderDepthBuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    glLoadIdentity();

    //fps count
    double currentTime = GetTimeAsDouble();
    nbFrames++;
    if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
        // printf and reset timer
        printf("%f ms/frame or %d\n", 1000.0/double(nbFrames), nbFrames);
        nbFrames = 0;
        lastTime += 1.0;
    }


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(zoomFactor, zoomFactor, zoomFactor));

    // view = glm::lookAt(
    //     glm::vec3(cameraPositionX, cameraPositionY, cameraPositionZ),
    //     glm::vec3(0.0f, 0.0f, 0.0f),
    //     glm::vec3(0.0f, 1.0f, 0.0f)
    // );

    projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 1000.0f);
    //viewMatrix = projection * view;
    viewProjMatrix = projection * viewMatrix;
    // glm::mat4 invViewProj = glm::inverse(viewProjMatrix);
    world->updateVisibility(viewProjMatrix, depthFBO);
    updateVBO();

    GLint modelLoc = glGetUniformLocation(programID, "model");
    GLint viewLoc = glGetUniformLocation(programID, "view");
    GLint projLoc = glGetUniformLocation(programID, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindTexture(GL_TEXTURE_2D, textureID);

    ibo->Bind();
    vbo->Bind();
    glEnableVertexAttribArray(0); // Vertex positions
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glEnableVertexAttribArray(1); // Vertex textures
    tbo->Bind();
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //To show with lines only

    glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    vbo->Unbind();
    tbo->Unbind();
    ibo->Unbind();
    //drawFrustum(invViewProj);

    glutSwapBuffers();
}

void Renderer::updateVBO() {
    std::vector<float> newVertices;
    std::vector<float> newTexCoords;
    std::vector<unsigned int> newIndices;

    unsigned int baseIndex = 0;

    for (Voxel voxel : world->voxels) {
        if (voxel.isActive()) {
            newVertices.insert(newVertices.end(), voxel.vertices.begin(), voxel.vertices.end());
            newTexCoords.insert(newTexCoords.end(), voxel.texCoords.begin(), voxel.texCoords.end());
            for (unsigned int index : voxel.indices) {
                newIndices.push_back(baseIndex + index);
            }
            baseIndex += voxel.vertices.size() / 3;
        }
    }

    // Update VBO and IBO with new data
    vbo->Bind();
    vbo->Update(newVertices.data(), newVertices.size() * sizeof(float));
    vbo->Unbind();

    tbo->Bind();
    tbo->Update(newTexCoords.data(), newTexCoords.size() * sizeof(float));
    tbo->Unbind();

    ibo->Bind();
    ibo->Update(newIndices.data(), newIndices.size());
    ibo->Unbind();
}

void Renderer::initializeDepthResources() {

    glGenFramebuffers(1, &depthFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE); // No color buffer is drawn to.
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "ERROR::FRAMEBUFFER:: Depth framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderDepthBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Render the scene to populate the depth buffer
    renderSceneToDepthBuffer();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderSceneToDepthBuffer() {
    glUseProgram(depthProgramID);
    glLoadIdentity();

    glm::mat4 model = model;
    glm::mat4 view = view;
    glm::mat4 projection = projection;
    //glm::mat4 viewMatrix = projection * view;

    GLint modelLoc = glGetUniformLocation(depthProgramID, "model");
    GLint viewLoc = glGetUniformLocation(depthProgramID, "view");
    GLint projLoc = glGetUniformLocation(depthProgramID, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    ibo->Bind();
    vbo->Bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
    vbo->Unbind();
    ibo->Unbind();
}
