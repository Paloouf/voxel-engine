#pragma once

#define WIDTH 800.0f
#define HEIGHT 600.0f
#define GL_GLEXT_PROTOTYPES
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <signal.h>
#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <map>
#include <sstream>
#include <cmath>
#include <chrono>
#include <thread>
#include "Voxel.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "World.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL.h"
#include "Frustum.hpp"


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
double GetTimeAsDouble();