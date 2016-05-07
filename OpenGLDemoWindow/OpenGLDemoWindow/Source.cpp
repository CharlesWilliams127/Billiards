#include "Engine.h"

int main()
{
	// create an engine object
	Engine engine;

	if (engine.init() == false)
	{
		return -1;
	}

	// check to see if bufferModel returns false
	if (engine.bufferModels() == false)
	{
		return -2;
	}

	// check to see if the shaders are used properly
	if (engine.useShaders() == false)
	{
		return -3;
	}

	// check to see if the game loop runs properly
	if (engine.gameLoop() == false)
	{
		return -4;
	}

	return 0;
}