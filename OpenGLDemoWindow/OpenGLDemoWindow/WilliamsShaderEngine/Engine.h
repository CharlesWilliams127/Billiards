#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>

#include "ShaderManager.h"
#include <string>
#include <iostream>
#include <vector>

using std::vector;

class Engine
{
private:
	// window pointer
	GLFWwindow* GLFWwindowPtr;

	unsigned int vertCount;

	GLuint vertArr;

	ShaderManager shaderManager;
public:
	// this will initialize the window
	bool init();

	bool bufferModel();

	bool useShaders();

	// game loop method
	bool gameLoop();

	Engine();
	~Engine();
};

