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
using glm::mat3;

class Camera
{
public:
	Transform transform;
	RigidBody rigidBody;

	// an update method that will move the camera
	void update(vec3 f, float deltaTime);

	void stop();

	Camera();

	~Camera();

private:
	// move or turn camera

	vec3 camLoc;
	vec3 camRot;

	mat3 rotMat;

	vec3 eye;
	vec3 center;
	vec3 up;

	mat4 lookAtMat;

	// zoom or cahnge aspect ratio
	float zoom;
	int width;
	int height;

	float fovy;
	float aspect;
	float zNear;
	float zFar;

	mat4 camMat;

	mat4 perspectiveMat;
};

