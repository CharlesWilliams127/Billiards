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

using std::vector;
using glm::vec2;
using glm::vec3;
using std::map;
using glm::mat4;

struct Transform
{
	vec3 loc;
	vec3 rot;
	vec3 size;
	mat4 transMatrix;
};

struct RigidBody
{
	vec3 vel;
	vec3 force;
	float mass;
};

enum Colliders
{
	colliderless,
	AABB,
	sphere
};

class Object
{
private:
	// collider attribute to keep track of what it is
	Colliders collider;

	// a filename to hold the texture file
	char* texFileName;

	// assign a rigidbody to the object
	RigidBody rigidBody;

	// these attributes are for detecting collisions
	float radius = transform.size.x;


public:

	// a Transform to hold the object's position, rotation, and scale
	Transform transform;

	Object(char* tFN, Colliders c);
	Object();
	~Object();

	// a getter for the rigidBody
	RigidBody getRigidBody();

	// sets velocity to 0
	void stop();

	// calculate the forces
	void calcForces(vec3 f, float deltaTime);

	// this method will update position based off of forces calculated in calcForces
	void move(float deltaTime);

	void draw();

	// detect collisions
	bool collidesWith(Object &otherObject);
};

