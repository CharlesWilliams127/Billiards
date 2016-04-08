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
#include <map>

using std::vector;
using glm::vec2;
using glm::vec3;
using std::map;
using glm::mat4;

class Engine
{
private:
	// window pointer
	GLFWwindow* GLFWwindowPtr;

	unsigned int vertCount;

	GLuint vertArr;

	ShaderManager shaderManager;

	vector <char*> texFiles;

	vector <unsigned int> texIDs;

	vector <Object> objects;
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

