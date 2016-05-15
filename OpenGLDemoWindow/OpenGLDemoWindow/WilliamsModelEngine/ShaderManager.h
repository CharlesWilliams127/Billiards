#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	// returns the program attribute
	GLuint getProgram() const;

	// will load shaders
	bool loadShaders(const char* vertexFile, const char* fragmentFile);
private:
	// index where the loaded shaders are stored on graphics card
	GLuint program;

	// helper method to help load shaders
	GLuint loadShader(const char* file, GLenum shaderType);
};

