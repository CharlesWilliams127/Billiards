#include "Camera.h"


Camera::Camera()
{
	rigidBody.vel = vec3(0, 0, 0);
	rigidBody.mass = 1.0f;
	rigidBody.force = vec3();

	transform.loc = { 0, 0, 2 };
	transform.rot = { 0, 0, 0 };

	rotMat =
		(mat3)glm::yawPitchRoll(transform.rot.y, transform.rot.x, transform.rot.z);

	eye = camLoc;
	center = eye + rotMat * vec3(0, 0, -1);
	up = rotMat * vec3(0, 1, 0);

	lookAtMat = glm::lookAt(eye, center, up);

	// zoom or cahnge aspect ratio
	zoom = 1.f;
	width = 800;
	height = 600;

	fovy = 3.14159 * .3f / zoom;
	aspect = (float)width / (float)height;
	zNear = .01f;
	zFar = 1000.f;

	perspectiveMat =
		glm::perspective(fovy, aspect, zNear, zFar);

	camMat = perspectiveMat * lookAtMat;

	//glUniformMatrix4fv(3, 1, GL_FALSE, &camMat[0][0]);
}

void Camera::update(vec3 f, float deltaTime)
{
	// calculate accelration based off of passed in force
	rigidBody.force = f;

	vec3 acceleration = rigidBody.force / rigidBody.mass;

	// caluculate dv
	vec3 dv = acceleration * deltaTime;

	// increment the velocity
	rigidBody.vel += dv;

	// calculate dr
	vec3 dr = rigidBody.vel * deltaTime;

	// increment the position
	transform.loc += dr;

	//perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

	rotMat =
		(mat3)glm::yawPitchRoll(transform.rot.y, transform.rot.x, transform.rot.z);

	vec3 eye = transform.loc;
	vec3 center = eye + rotMat * vec3(0, 0, -1);
	vec3 up = rotMat * vec3(0, 1, 0);

	lookAtMat = glm::lookAt(eye, center, up);

	camMat = perspectiveMat * lookAtMat;

	glUniformMatrix4fv(3, 1, GL_FALSE, &camMat[0][0]);
}

void Camera::stop()
{

	rigidBody.vel = vec3(0, 0, 0);
}

Camera::~Camera()
{
}
