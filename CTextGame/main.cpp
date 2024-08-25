#include <stdio.h>

#include "GameEngine.h"

int main()
{
	if (GameEngineInit() == false)
	{
		return false;
	}

	return GameEngineStart();
}