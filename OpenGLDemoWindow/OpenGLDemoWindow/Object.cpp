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
	//mat4 identity =
	//{
	//	1, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	0, 0, 0, 1
	//};

	// these methods draw each individual object to the screen
	transform.transMatrix = glm::translate(transform.loc) * glm::scale(transform.size) * glm::yawPitchRoll(transform.rot.y, transform.rot.x, transform.rot.z);

	//glUniformMatrix4fv(3, 1, GL_FALSE, &identity[0][0]);
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
		float mag = sqrt((pow(distance.x, 2) + pow(distance.y, 2) + pow(distance.z, 2)));

		//cout << mag << endl;

		// check to see if the distance is greater than the objects radii
		if (mag > (transform.size.x + otherObject.transform.size.x))
		{
			return false;
		}
	}

	// check to see if both are AABB
	if (collider == AABB && otherObject.collider == AABB)
	{
		// check the mins and maxes on the x axis
		if (((transform.loc.x - transform.size.x) < (otherObject.transform.loc.x + otherObject.transform.size.x)) || ((transform.loc.x + transform.size.x) > (otherObject.transform.loc.x - otherObject.transform.size.x)))
		{
			return false;
		}

		// check the mins and maxes on the y axis
		if (((transform.loc.y - transform.size.y) < (otherObject.transform.loc.y + otherObject.transform.size.y)) || ((transform.loc.y + transform.size.y) > (otherObject.transform.loc.y - otherObject.transform.size.y)))
		{
			return false;
		}

		// check the mins and maxes on the z axis
		if (((transform.loc.z - transform.size.z) < (otherObject.transform.loc.z + otherObject.transform.size.z)) || ((transform.loc.y + transform.size.z) > (otherObject.transform.loc.z - otherObject.transform.size.z)))
		{
			return false;
		}
	}

	// check if this object is a sphere and it's colliding with a AABB
	if (collider == sphere && otherObject.collider == AABB)
	{
		// set sqrDistance to 0
		float sqrDistance = 0;

		// current is left of other
		if (transform.loc.x < (otherObject.transform.loc.x - otherObject.transform.size.x))
		{
			sqrDistance += pow((otherObject.transform.loc.x - otherObject.transform.size.x) - transform.loc.x, 2);
		}

		// current is right of other
		if (transform.loc.x > (otherObject.transform.loc.x + otherObject.transform.size.x))
		{
			sqrDistance += pow( transform.loc.x - (otherObject.transform.loc.x + otherObject.transform.size.x), 2);
		}

		// current is left of other
		if (transform.loc.y < (otherObject.transform.loc.y - otherObject.transform.size.y))
		{
			sqrDistance += pow((otherObject.transform.loc.y - otherObject.transform.size.y) - transform.loc.y, 2);
		}

		// current is right of other
		if (transform.loc.y >(otherObject.transform.loc.y + otherObject.transform.size.y))
		{
			sqrDistance += pow(transform.loc.y - (otherObject.transform.loc.y + otherObject.transform.size.y), 2);
		}

		// current is left of other
		if (transform.loc.z < (otherObject.transform.loc.z - otherObject.transform.size.z))
		{
			sqrDistance += pow((otherObject.transform.loc.z - otherObject.transform.size.z) - transform.loc.z, 2);
		}

		// current is right of other
		if (transform.loc.z >(otherObject.transform.loc.z + otherObject.transform.size.z))
		{
			sqrDistance += pow(transform.loc.z - (otherObject.transform.loc.z + otherObject.transform.size.z), 2);
		}

		if (sqrDistance > pow(transform.size.x, 2))
		{
			return false;
		}
	}

	// this means the objects are colliding!
	return true;
}
