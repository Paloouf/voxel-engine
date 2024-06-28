#include "../include/main.hpp"


Renderer* renderer;
float red=1.0f, blue=1.0f, green=1.0f;
float angle = 1.0f;

void resize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = 1.0 * w /h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void    processNormalKeys(unsigned char key, int x, int y){
    (void)x;
    (void)y;
    if (key == 27){
        delete renderer;
        exit(0);
    }
    else if (key == 'r') {
		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_ALT)
			red = 0.0;
		else
			red = 1.0;
	}
    const float moveSpeed = 5.1f;
    switch (key) {
        case 'w':
            renderer->moveCamera(0.0f, 0.0f, -moveSpeed); // Move forward
            break;
        case 's':
            renderer->moveCamera(0.0f, 0.0f, moveSpeed); // Move backward
            break;
        case 'a':
            renderer->moveCamera(-moveSpeed, 0.0f, 0.0f); // Move left
            break;
        case 'd':
            renderer->moveCamera(moveSpeed, 0.0f, 0.0f); // Move right
            break;
        case 'q':
            renderer->moveCamera(0.0f, moveSpeed, 0.0f); // Move up
            break;
        case 'e':
            renderer->moveCamera(0.0f, -moveSpeed, 0.0f); // Move down
            break;
    }
}

void    processSpecialKeys(int key, int x, int y){
    (void)x;
    (void)y;
    switch(key) {
		case GLUT_KEY_F1 :
				red = 1.0;
				green = 0.0;
				blue = 0.0; break;
		case GLUT_KEY_F2 :
				red = 0.0;
				green = 1.0;
				blue = 0.0; break;
		case GLUT_KEY_F3 :
				red = 0.0;
				green = 0.0;
				blue = 1.0; break;
	}
}

void displayWrapper() {
    
    if (renderer) renderer->draw();
}

int lastMouseX = 0;
int lastMouseY = 0;
bool isLeftButtonPressed = false;
bool isRightButtonPressed = false;

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isLeftButtonPressed = true;
            lastMouseX = x;
            lastMouseY = y;
        } else if (state == GLUT_UP) {
            isLeftButtonPressed = false;
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            isRightButtonPressed = true;
            lastMouseX = x;
            lastMouseY = y;
        } else if (state == GLUT_UP) {
            isRightButtonPressed = false;
        }
    }
    if (button == 3)
    {
        //means im zooming
        renderer->zoomFactor += renderer->zoomSpeed;
    }
    if (button == 4)
    {
        //means im dezooming
        renderer->zoomFactor -= renderer->zoomSpeed;
    }
    //std::cout << button << " " << state << " " << x << " " << y << std::endl;
}

void mouseMotion(int x, int y) {
    if (isLeftButtonPressed) {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        // Adjust rotation based on mouse movement
        // Update your rotation matrix or angle here
        // For example:
        renderer->rotationAngleX += deltaY * renderer->sensitivity;
        renderer->rotationAngleY += deltaX * renderer->sensitivity;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay(); // Request a redraw
    }
    if (isRightButtonPressed) {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        // Adjust the camera position based on mouse movement
        renderer->cameraPositionX += deltaX * renderer->panSpeed;
        renderer->cameraPositionY += deltaY * renderer->panSpeed;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay(); // Request a redraw
    }
}

void mouseWheel(int wheel, int direction, int x, int y) {
    std::cout << wheel << x << y << std::endl;
    if (direction > 0) {
        // Zoom in
        renderer->zoomFactor += renderer->zoomSpeed;
    } else {
        // Zoom out
        renderer->zoomFactor -= renderer->zoomSpeed;
    }

    // Clamp zoom factor if needed
    renderer->zoomFactor = std::max(renderer->minZoom, std::min(renderer->maxZoom, renderer->zoomFactor));

    glutPostRedisplay(); // Request a redraw
}

double GetTimeAsDouble() {
    using namespace std::chrono;
    using SecondsFP = std::chrono::duration<double>;
    return duration_cast<SecondsFP>(high_resolution_clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Voxel Engine");

    glEnable(GL_DEPTH_TEST);

    World world(15);
    renderer = new Renderer(&world);
    renderer->lastTime = GetTimeAsDouble();
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(resize);
    glutIdleFunc(displayWrapper);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    delete renderer;
    return 0;
}
