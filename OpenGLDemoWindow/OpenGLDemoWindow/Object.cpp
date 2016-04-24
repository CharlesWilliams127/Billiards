#include "Object.h"


Object::Object()
{
}

Object::Object(char * tFN, Colliders c)
{
	// assign values to the rigidBody
	rigidBody.force = vec3(0, 0, 0);
	rigidBody.vel = vec3(0, 0, 0);
	rigidBody.mass = 1;

	texFileName = tFN;

	collider = c;

	// assign radii and width and height
}

Object::~Object()
{
}

RigidBody Object::getRigidBody()
{
	return rigidBody;
}

void Object::stop()
{
	rigidBody.vel = vec3(0, 0, 0);
}

void Object::draw()
{
	// these methods draw each individual object to the screen
	transform.transMatrix = glm::translate(transform.loc) * glm::scale(transform.size) * glm::yawPitchRoll(transform.rot.y, transform.rot.x, transform.rot.z);
	glUniformMatrix4fv(2, 1, GL_FALSE, &transform.transMatrix[0][0]);
}

void Object::calcForces(vec3 f, float deltaTime)
{
	// calculate accelration based off of passed in force
	rigidBody.force = f;

	vec3 acceleration = rigidBody.force / rigidBody.mass;

	// caluculate dv
	vec3 dv = acceleration * deltaTime;

	// increment the velocity
	rigidBody.vel += dv;
}

void Object::move(float deltaTime)
{
	// calculate dr
	vec3 dr = rigidBody.vel * deltaTime;

	// increment the position
	transform.loc += dr;
}

bool Object::collidesWith(Object & otherObject)
{
	// if either object has the colliderless attribute then they are not colliding
	if (collider == colliderless || otherObject.collider == colliderless)
	{
		return false;
	}

	// if both objects are spheres
	if (collider == sphere && otherObject.collider == sphere)
	{
		// get the distance between the objects
		vec3 distance = transform.loc - otherObject.transform.loc;

		// get the magnitude of the distance
		float mag = sqrt((pow(distance.x, 2) + pow(distance.y, 2)));
	}
}
