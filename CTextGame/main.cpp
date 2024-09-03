#include <stdio.h>

#include <Engine/GameEngine.h>

int main()
{
	if (GameEngineInit() == false)
	{
		return false;
	}

	return GameEngineStart();
}