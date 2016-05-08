#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <math.h>

#include "Model.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Object.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>

using std::vector;
using glm::vec2;
using glm::vec3;
using std::map;
using glm::mat4;
using std::cout;
using std::endl;
using std::string;
using std::istringstream;

struct Vertex
{
	vec3 loc;
	vec2 uv;
	vec3 normal;
};

struct VertInd
{
	unsigned int locInd, uvInd, normInd;
};

class Model
{
private:
	unsigned int vertCount;

	GLuint vertArr;
public:
	Model();

	// this is the method that will buffer the models
	bool buffer(string objFile);

	// this will render and draw the model
	void render();

	~Model();
};
