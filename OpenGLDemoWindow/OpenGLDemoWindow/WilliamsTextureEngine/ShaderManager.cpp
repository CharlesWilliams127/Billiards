#include "ShaderManager.h"



ShaderManager::ShaderManager()
{
	// initialize program to 0
	program = 0;
}

ShaderManager::~ShaderManager()
{
}

GLuint ShaderManager::getProgram() const
{
	return program;
}

bool ShaderManager::loadShaders(const char * vertexFile, const char * fragmentFile)
{
	// call loadShader and load the	VERTEX shader
	GLuint vShader = loadShader(vertexFile, GL_VERTEX_SHADER);

	// check for errors, return 0 if loadShader fails
	if (vShader == 0)
	{
		return 0;
	}

	// call loadShader and load the	FRAGMENT shader
	GLuint fShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	// check for errors, return 0 if loadShader fails
	if (fShader == 0)
	{
		return 0;
	}

	// create a new program
	program = glCreateProgram();

	// attatch the two shaders to the program
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	// link the program
	glLinkProgram(program);

	// determine if the program linked correctly
	GLint programLink;
	glGetProgramiv(program, GL_LINK_STATUS, &programLink);

	// mostly the same as printing out the log for shaders
	if (programLink == 0)
	{
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		// array of chars to hold log
		GLchar* programLog = new GLchar[logLength];
		glGetProgramInfoLog(program, logLength, 0, programLog);

		// print the log
		cout << "The program failed to compile with the following error: " << programLog << endl;

		// delete the program and the log
		glDeleteProgram(program);
		delete[] programLog;

		// return false
		return false;
	}
	else
	{
		// linked correctly
		return true;
	}

	return false;
}

GLuint ShaderManager::loadShader(const char * file, GLenum shaderType)
{
	// first, open the file using a binary reader to read the whole file
	ifstream inFile(file, ios::binary);

	// check if the file is opened successfully
	if (inFile.is_open())
	{
		// seek and get the length
		inFile.seekg(0, ios::end);
		int length = (int)inFile.tellg();

		// once end is found then seek back to the beginning
		inFile.seekg(0, ios::beg);

		// make an array to hold the file
		char* fileContents = new char[length + 1];

		// read file and set null pointer
		inFile.read(fileContents, length);
		fileContents[length] = 0;

		// close the file
		inFile.close();

		// if file was opened and contents were read successfully
		// create a new GLuint variable to hold the index of the object
		GLuint shader = glCreateShader(shaderType);

		// call the shader source
		glShaderSource(shader, 1, &fileContents, 0);

		// compile the shader
		glCompileShader(shader);

		// delete the character array to prevent memory leaks
		delete[] fileContents;

		// check to see if the shader compiled
		// create a new GLint variable to store results
		GLint compileResult;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

		// check if the compile succeeded
		if (compileResult == 0)
		{
			// create a GLint to hold the log length
			GLint logLength;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

			// call glGetShaderInfoLog to get the log and print it
			GLchar* shaderLog = new GLchar[logLength];
			glGetShaderInfoLog(shader, logLength, 0, shaderLog);

			cout << "The shader failed to compile with the following error: " << shaderLog << endl;
			
			// delete the shader and log array
			glDeleteShader(shader);
			delete[] shaderLog;

			// return 0 to signify failure
			return 0;
		}
		else
		{
			// return the shader if compiling succeeded
			return shader;
		}
	}
	else // if there is an error in opening the file
	{
		cout << "Error opening shader file." << endl;
		return 0;
	}
}
