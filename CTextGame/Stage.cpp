#include "Stage.h"
#include "Renderer.h"
#include "File.h"
#include "Game.h"
#include "UIRenderer.h"

#include <Windows.h>

// COMMON //

#define AddStage(stgaeName) \
	initHandler[(int)StageType::##stgaeName]		= On##stgaeName##Init;		\
	inputHandler[(int)StageType::##stgaeName]		= On##stgaeName##Input;		\
	processHandler[(int)StageType::##stgaeName]		= On##stgaeName##Process;		\
	renderHandler[(int)StageType::##stgaeName]		= On##stgaeName##Render

bool(*initHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*inputHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*processHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*renderHandler[(int)StageType::STAGE_TYPE_COUNT])();

StageType currentStageType;

bool StageInit()
{
	AddStage(Title);
	AddStage(Game);
	AddStage(Over);

	return true;
}

bool SetStage(StageType type)
{
	if (type == StageType::STAGE_TYPE_COUNT)
	{
		return false;
	}

	currentStageType = type;
    return initHandler[(int)currentStageType]();
}

int StageInput()
{
	inputHandler[(int)currentStageType]();
	return 0;
}

int StageProcess()
{
	processHandler[(int)currentStageType]();
	return 0;
}

int StageRender()
{
	renderHandler[(int)currentStageType]();
	return 0;
}










// Title //
bool OnTitleInit()
{
	return true;
}

int OnTitleInput()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (SetStage(StageType::Game) == false)
		{
			__debugbreak();
		}
		return 0;
	}

	return 0;
}

int OnTitleProcess()
{
	return 0;
}

int OnTitleRender()
{	
	CopyDataToRendBuffer({ 13, 2 }, "Shooting Game");

	CopyDataToRendBuffer({ 12, 5 }, "------------");
	CopyDataToRendBuffer({ 14, 6 }, "1. Game");
	CopyDataToRendBuffer({ 12, 7 }, "------------");

	return 0;
}








// Game
bool OnGameInit()
{
	return GameInit();
}

int OnGameInput()
{
	return GameInput();
}

int OnGameProcess()
{
	return GameProcess();
}

int OnGameRender()
{
	GameRender();
	UIRender();
	return 0;
}






// OVER //

bool OnOverInit()
{
	return true;
}

int OnOverInput()
{
	if (GetAsyncKeyState(VK_F2))
	{
		if (SetStage(StageType::Game) == false)
		{
			__debugbreak();
		}
		return 0;
	}
	return 0;
}

int OnOverProcess()
{
	return 0;
}

int OnOverRender()
{
	CopyDataToRendBuffer({ 13, 2 }, "Game Over");
	return 0;
}
