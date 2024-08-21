#include <stdio.h>

#include "GameEngine.h"

int main()
{
	if (GameEngine::Init() == false)
	{
		return false;
	}

	return GameEngine::Start();
}