#pragma once

#define WIDTH 1920
#define HEIGHT 1080
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
// #include <GL/glew.h>
// #include <GL/freeglut.h>
#include <chrono>
#include <thread>
#include "Voxel.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);