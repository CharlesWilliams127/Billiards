#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <math.h>

#include "ShaderManager.h"
#include "Object.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using std::vector;
using glm::vec2;
using glm::vec3;
using std::map;
using glm::mat4;
using std::cout;
using std::endl;

struct Vertex
{
	vec3 loc;
	vec2 uv;
};

//struct Object
//{
//	char* texFileName;
//	Transform transform;
//};

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

	// constants for tracking forces
	const float FORCE = 200;
	const float FORCE_FRICTION = -1;

	// this represents if the cue ball is in play
	bool inPlay = false;

	// variables for tracking time
	float currTime;
	float prevFrameTime;
	float deltaTime;

public:
	// this will initialize the window
	bool init();

	vec3 getMousePos();

	bool bufferModel();

	bool useShaders();

	// game loop method
	bool gameLoop();

	void drawObject();

	Engine();
	~Engine();
};

