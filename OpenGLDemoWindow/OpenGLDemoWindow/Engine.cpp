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

Engine::Engine()
{
}

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
	// ball identity cooresponds

	texFiles.push_back("textures/cueball.png");
	texFiles.push_back("textures/15ball.png");
	texFiles.push_back("textures/1ball.png");
	texFiles.push_back("textures/2ball.png");
	texFiles.push_back("textures/3ball.png");
	texFiles.push_back("textures/4ball.png");
	texFiles.push_back("textures/5ball.png");
	texFiles.push_back("textures/6ball.png");
	texFiles.push_back("textures/7ball.png");
	texFiles.push_back("textures/8ball.png");
	texFiles.push_back("textures/9ball.png");
	texFiles.push_back("textures/10ball.png");
	texFiles.push_back("textures/11ball.png");
	texFiles.push_back("textures/12ball.png");
	texFiles.push_back("textures/13ball.png");
	texFiles.push_back("textures/14ball.png");
	texFiles.push_back("textures/pool_table.png");

	// assign each texture file an usigned int to use as its texture ID
	for (unsigned int i = 0; i < texFiles.size(); i++)
	{
		texIDs.push_back(i);
	}


	//create the pool table
	objects.push_back(Object(texFiles[0], colliderless));

	// create all balls
	for (int i = 1; i < texFiles.size(); i++)
	{
		objects.push_back(Object(texFiles[i], sphere));
	}

	// create all six pockets
	for (int i = 0; i < 6; i++)
	{
		pockets.push_back(Pocket());
		pockets[i].collider = sphere;
	}

	// pool table
	objects[0].transform.loc = vec3(0, 0, 0);
	objects[0].transform.size = vec3(1, 1, 1);
	objects[0].transform.rot = vec3(0, 0, 0);

	// assign pockets
	// top left
	pockets[0].transform.loc = vec3(-.85, -.85, 0);
	pockets[0].transform.size = vec3(.05, .05, 1);
	pockets[0].transform.rot = vec3(0, 0, 0);

	// top middle
	pockets[1].transform.loc = vec3(0, -.85, 0);
	pockets[1].transform.size = vec3(.05, .05, 1);
	pockets[1].transform.rot = vec3(0, 0, 0);

	// top right
	pockets[2].transform.loc = vec3(.85, -.85, 0);
	pockets[2].transform.size = vec3(.05, .05, 1);
	pockets[2].transform.rot = vec3(0, 0, 0);

	// bottom right
	pockets[3].transform.loc = vec3(.85, .85, 0);
	pockets[3].transform.size = vec3(.05, .05, 1);
	pockets[3].transform.rot = vec3(0, 0, 0);

	// bottom middle
	pockets[4].transform.loc = vec3(0, .85, 0);
	pockets[4].transform.size = vec3(.05, .05, 1);
	pockets[4].transform.rot = vec3(0, 0, 0);

	// bottom left
	pockets[5].transform.loc = vec3(-.85, .85, 0);
	pockets[5].transform.size = vec3(.05, .05, 1);
	pockets[5].transform.rot = vec3(0, 0, 0);

	// ball loop that will set up sizes for each ball
	for (int i = 1; i < objects.size(); i++)
	{
		// x is 1.33% of the y
		objects[i].transform.size = vec3(.04, .05, 1);
		objects[i].transform.rot = vec3(0, 0, 0);
	}

	// pool ball locations
	// balls increment by .05 in the x direction and .04 in the y
	// cue ball
	objects[1].transform.loc = vec3(.5, 0, 0);
	//row 1
	objects[2].transform.loc = vec3(-.35, 0, 0);
	// row 2
	objects[12].transform.loc = vec3(-.43, .06, 0);
	objects[11].transform.loc = vec3(-.43, -.06, 0);
	// row 3
	objects[10].transform.loc = vec3(-.51, .12, 0);
	objects[9].transform.loc = vec3(-.51, 0, 0);
	objects[7].transform.loc = vec3(-.51, -.12, 0);
	// row 4
	objects[6].transform.loc = vec3(-.59, .18, 0);
	objects[13].transform.loc = vec3(-.59, .06, 0);
	objects[8].transform.loc = vec3(-.59, -.06, 0);
	objects[14].transform.loc = vec3(-.59, -.18, 0);
	// row 5
	objects[16].transform.loc = vec3(-.67, .24, 0);
	objects[3].transform.loc = vec3(-.67, .12, 0);
	objects[15].transform.loc = vec3(-.67, .0, 0);
	objects[4].transform.loc = vec3(-.67, -.12, 0);
	objects[5].transform.loc = vec3(-.67, -.24, 0);

	// alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	currTime = glfwGetTime();

	// render in wire frame mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);

	return true;
}

vec3 Engine::getMousePos()
{
	return vec3();
}

bool Engine::bufferModels()
{
	if (model.buffer("models/sphere.obj") == false)
	{
		return false;
	}
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

	camera = Camera();

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

	// values that will hold the mouse's position
	double mouseX;
	double mouseY;

	vec3 unit;

	// loop until the window is closed by the user
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		// update the game time
		prevFrameTime = currTime;
		currTime = glfwGetTime();
		deltaTime = currTime - prevFrameTime;

		// clear the canvas
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// this will apply an initial force whenever the cueball stops, representing the pool stick striking it
		float mag;
		vec3 mousePos;
		vec3 force;

		// if the cue ball is not already moving or in play, then allow the player to move it
		if (keyIsDown[GLFW_MOUSE_BUTTON_LEFT] && !keyWasDown[GLFW_MOUSE_BUTTON_LEFT] && inPlay == false)
		{
			// reset the friction counter
			frictionCounter = 0;

			// gets the mouse location
			double mouseX;
			double mouseY;

			// method that gets the cursor location
			glfwGetCursorPos(GLFWwindowPtr, &mouseX, &mouseY);

			int width, height;

			glfwGetWindowSize(GLFWwindowPtr, &width, &height);

			//cout << mouseX << ", " << mouseY << endl;

			mouseX = (mouseX / 400) - 1;
			mouseY = (mouseY / 300) - 1;

			//cout << mouseX << ", " << mouseY << endl;

			// this is the vector that will hold the vector connecting the cue ball to the mouse
			vec3 ballToMouse = vec3(mouseX - objects[1].transform.loc.x, -mouseY - objects[1].transform.loc.y, 0);

			// find the magnitude
			mag = sqrt((pow(ballToMouse.x, 2)) + (pow(ballToMouse.y, 2)));

			// find the unit vector
			unit = vec3(ballToMouse.x / mag, ballToMouse.y / mag, 0);

			// this is the initial force
			force = vec3(unit.x * FORCE, unit.y * FORCE, 0);

			// multiply the initial force by that to find the final force vector
			objects[1].calcForces(force, deltaTime);

			// set the in Play attribute to true
			inPlay = true;
		}

		if (inPlay == true)
		{
			// calculate a frictional force
			vec3 forceFriction = vec3(unit.x * FORCE_FRICTION, unit.y * FORCE_FRICTION, 0);

			// apply the frictional force
			objects[1].calcForces(forceFriction, deltaTime);

			//cout << objects[1].getRigidBody().vel.x << " " << objects[1].getRigidBody().vel.y << endl;

			// set a counter
			frictionCounter += FORCE_FRICTION;

			//cout << frictionCounter << endl << FORCE << endl;

			// check if frictional force exceeds initial force
			if (frictionCounter <= -FORCE)
			{
				// if frictional force is greater than the negative initial force then stop the object
				objects[1].stop();

				// allow the cue ball to be hit again
				inPlay = false;
			}
		}

		// actually move the object
		objects[1].move(deltaTime);

		// check for collisions
		// for the purpose of checking collisions, object 1 is the cue ball
		for (int i = 1; i < objects.size(); i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
			{
				if (objects[i].collidesWith(objects[j]))
				{
					cout << "Ball " << i << " is colliding with ball " << j << endl;

					break;
				}
			}
			for (int h = 0; h < pockets.size(); h++)
			{
				if (pocketCollision(pockets[h], objects[i]))
				{
					cout << "Ball " << i << " is colliding with pocket " << h << endl;
				}
			}
		}

		// if the object goes off of the screen
		if (objects[1].transform.loc.x > 1)
		{
			objects[1].transform.loc.x = -1;
		}

		if (objects[1].transform.loc.x < -1)
		{
			objects[1].transform.loc.x = 1;
		}

		if (objects[1].transform.loc.y > 1)
		{
			objects[1].transform.loc.y = -1;
		}

		if (objects[1].transform.loc.y < -1)
		{
			objects[1].transform.loc.y = 1;
		}
		//cout << objects[1].transform.loc.x << endl;

		// update the camera

		//camera.update(vec3(), deltaTime);

		for (int i = 0; i < objects.size(); i++)
		{
			// call the current objects draw method
			objects[i].draw();

			// render the game objects
			model.render();
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, texIDs[i]);
			// unbind after drawing
		}

		glfwSwapBuffers(GLFWwindowPtr);

		// process queued window, mouse/keyboard callback events
		//keyWasDown = keyIsDown;
		glfwPollEvents();

		camera.update(vec3(0, 0, 0), deltaTime);

		if (keyIsDown[GLFW_KEY_LEFT])
		{
			//cout << "Left" << endl;
			camera.update(vec3(-40, 0, 0), deltaTime);
		}
		else
		{
			camera.stop();
		}

		if (keyIsDown[GLFW_KEY_RIGHT])
		{
			//cout << "Right" << endl;
			camera.update(vec3(40, 0, 0), deltaTime);
		}
		else
		{
			camera.stop();
		}

		if (keyIsDown[GLFW_KEY_UP])
		{
			//cout << "Up" << endl;
			camera.update(vec3(0, 40, 0), deltaTime);
		}
		else
		{
			camera.stop();
		}

		if (keyIsDown[GLFW_KEY_DOWN])
		{
			//cout << "Down" << endl;
			camera.update(vec3(0, -40, 0), deltaTime);
		}
		else
		{
			camera.stop();
		}

		// check to see if escape key is pressed
		if (keyIsDown[GLFW_KEY_ESCAPE])
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}

	}

	for (int i = 0; i < texIDs.size(); i++)
	{
		glDeleteTextures(1, &texIDs[i]);
	}

	glfwTerminate();

	return true;
}

bool Engine::pocketCollision(Pocket &pocket, Object &object)
{

	// if either object has the colliderless attribute then they are not colliding
	//if (pocket.collider == colliderless || object.collider == colliderless)
	//{
	//	return false;
	//}

	// get the distance between the objects
	vec3 distance = object.transform.loc - pocket.transform.loc;

	// get the magnitude of the distance
	float mag = sqrt((pow(distance.x, 2) + pow(distance.y, 2) + pow(distance.z, 2)));

	//cout << mag << endl;

	// check to see if the distance is greater than the objects radii
	if (mag > (pocket.transform.size.x + object.transform.size.x))
	{
		return false;
	}
	else
	{
		return true;
	}
}

Engine::~Engine()
{
}
