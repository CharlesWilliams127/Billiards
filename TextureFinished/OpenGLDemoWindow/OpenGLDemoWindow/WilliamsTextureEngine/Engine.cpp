#include "Engine.h"

// anonymous namespace
namespace 
{
	map<int, bool> keyIsDown;
	map<int, bool> keyWasDown;

	void mouseClick(GLFWwindow * windowPtr, int button, int action, int mods)
	{
		keyIsDown[button] = action;
	}

	void keyCallback(GLFWwindow * windowPtr, int key, int scancode, int action, int mods)
	{
		keyIsDown[key] = action;
	}
}

struct Vertex
{
	vec3 loc;
    vec2 uv;
};

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

	// set the click function
	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);

	// set the keypress function
	glfwSetKeyCallback(GLFWwindowPtr, keyCallback);

	// initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	// assign texture files to vector
	texFiles.push_back("textures/TestTexture.png");
	texFiles.push_back("textures/ball_8.jpg");
	texFiles.push_back("textures/ball_3.jpg");
	texFiles.push_back("textures/ball_11.jpg");
	texFiles.push_back("textures/pool_table.png");

	// assign each texture file an usigned int to use as its texture ID
	for (unsigned int i = 0; i < texFiles.size(); i++)
	{
		texIDs.push_back(i);
	}

	return true;
}

bool Engine::bufferModel()
{
	// QUAD

	// define the vertex locations
	vector<vec3> locs =
	{
		{ 1, 1, 0 },
		{ -1, 1, 0 },
		{ -1, -1, 0 },
		{ 1, -1, 0 } 
	};

	// connecting the dots
	vector <unsigned int>
		locInds =
	{ 0, 1, 2, 0, 2, 3 };

	// add UV locations and vertices
	vector <vec2> uvs 
	{
		{1, 1},
		{0, 1},
		{0, 0},
		{1, 0}
	};

	// connect UV dots
	vector <unsigned int>
		uvInds =
	{ 0, 1, 2, 0, 2, 3 };

	// assign vertCount
	vertCount = locInds.size();

	// duplicate the vertices into a single buffer
	vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i].loc = locs[locInds[i]];
		vertBufData[i].uv = uvs[uvInds[i]];
	}

	GLuint vertBuf;

	// generate the vertex arrays and buffers
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	// bind both of them
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// store the data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertCount, &vertBufData[0], GL_STATIC_DRAW);

	// enable the attribute
	glEnableVertexAttribArray(0);

	// location attribute
	glVertexAttribPointer(
		0, // attribute index
		3, // number of components (x, y, z)
		GL_FLOAT, // type of data
		GL_FALSE, // normalize data?
		sizeof(Vertex), // stride (bytes per vertex)
		0); // offset to this attribute

	// enable the attribute
	glEnableVertexAttribArray(1);

	// uv attribute
	glVertexAttribPointer(
		1, // attribute index
		2, // number of components (x, y)
		GL_FLOAT, // type of data
		GL_FALSE, // normalize data?
		sizeof(Vertex), // stride (bytes per vertex)
		(void*)sizeof(vec3)); // offset to this attribute

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
	// set a variable to pass into the texture whatever
	//unsigned int texID;

	// loop that will load all shaders
	for (int i = 0; i < texFiles.size(); i++)
	{
		// LOAD BEFORE GAME LOOP
		// this variable holds the texture file
		char* textureFile = texFiles[i];

		FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(textureFile, 0), textureFile);

		// check if load failed
		if (image == nullptr)
		{
			return false;
		}

		// convert the original image into a 32bit bmp
		FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);

		// unload the image from memory
		FreeImage_Unload(image);

		// generate and bind a new texture
		glGenTextures(1, &texIDs[i]);
		glBindTexture(GL_TEXTURE_2D, texIDs[i]);

		// upload the texture bytes
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit), FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32Bit));

		// set min filter to linear
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// unload the image from RAM
		FreeImage_Unload(image32Bit);

		// unbind the texture when done
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int counter = 0;

	// loop until the window is closed by the user
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		// clear the canvas
		glClear(GL_COLOR_BUFFER_BIT);

		// render the game objects
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, texIDs[counter]);
		// unbind after drawing

		glfwSwapBuffers(GLFWwindowPtr);

		// process queued window, mouse/keyboard callback events
		keyWasDown = keyIsDown;
		glfwPollEvents();

		// check to see if escape key is pressed
		if (keyIsDown[GLFW_KEY_ESCAPE])
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}

		if (keyIsDown[GLFW_MOUSE_BUTTON_LEFT] && keyWasDown[GLFW_MOUSE_BUTTON_LEFT] == false)
		{
			counter++;
		}

		if (counter >= texIDs.size())
		{
			counter = 0;
		}

	}

	for (int i = 0; i < texIDs.size(); i++)
	{
		glDeleteTextures(1, &texIDs[i]);
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
