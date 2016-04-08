#include "Engine.h"



bool Engine::init()
{
	// initialize the window library
	if (glfwInit() == GL_FALSE)
	{
		return false;
	}

	// create the window
	GLFWwindowPtr = glfwCreateWindow(800, 600, "Williams DSA1 Engine", NULL, NULL);

	// set the window pointer to the currently active window
	// check to see if it fails in creating the window
	if (GLFWwindowPtr != nullptr)
	{
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else
	{
		glfwTerminate();
		return false;
	}

	// initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	return true;
}

bool Engine::bufferModel()
{
	// QUAD

	// define the vertex locations
	vector<glm::vec3> locs = {
		{ .9, .9, 0 },
		{ -.9, .9, 0 },
		{ -.9, -.9, 0 },
		{ .9, -.9, 0 } };

	// connecting the dots
	vector <unsigned int>
		locInds =
	{ 0, 1, 2, 0, 2, 3 };

	// assign vertCount
	vertCount = locInds.size();

	// duplicate the vertices into a single buffer
	vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = locs[locInds[i]];
	}

	GLuint vertBuf;

	// generate the vertex arrays and buffers
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	// bind both of them
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// store the data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertCount, &vertBufData[0], GL_STATIC_DRAW);

	// enable the attribute
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0, // attribute index
		3, // number of components (x, y, z)
		GL_FLOAT, // type of data
		GL_FALSE, // normalize data?
		sizeof(glm::vec3), // stride (bytes per vertex)
		0); // offset to this attribute

			// unbind when finished
	glBindVertexArray(0);

	// set the color to cornflower blue, #throwbackthursday
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	return true;
}

bool Engine::useShaders()
{
	// call the loadShaders method
	if (shaderManager.loadShaders("shaders/vShader.glsl", "shaders/fShader.glsl") == true)
	{
		glUseProgram(shaderManager.getProgram());
		return true;
	}
	else
	{
		return false;
	}
}

bool Engine::gameLoop()
{
	// loop until the window is closed by the user
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		// clear the canvas
		glClear(GL_COLOR_BUFFER_BIT);

		// render the game objects
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		glBindVertexArray(0);
		// unbind after drawing

		glfwSwapBuffers(GLFWwindowPtr);

		// process queued window, mouse/keyboard callback events
		glfwPollEvents();
	}

	glfwTerminate();

	return true;
}

Engine::Engine()
{
}


Engine::~Engine()
{
}
