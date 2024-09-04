#include "Stage.h"

#include <Renderer/Renderer.h>

#include <Stage/GameStage/Game/Game.h>

#include <Windows.h>

// COMMON //

#define AddStage(stgaeName) \
	_initHandler[(int)StageType::##stgaeName]		= On##stgaeName##Init;			\
	_inputHandler[(int)StageType::##stgaeName]		= On##stgaeName##Input;			\
	_processHandler[(int)StageType::##stgaeName]	= On##stgaeName##Process;		\
	_renderHandler[(int)StageType::##stgaeName]		= On##stgaeName##Render

bool(*_initHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*_inputHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*_processHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*_renderHandler[(int)StageType::STAGE_TYPE_COUNT])();

// Title
bool OnTitleInit();
int OnTitleInput();
int OnTitleProcess();
int OnTitleRender();

// Game
bool OnGameInit();
int OnGameInput();
int OnGameProcess();
int OnGameRender();

// Win
bool OnWinInit();
int OnWinInput();
int OnWinProcess();
int OnWinRender();

// Game Over
bool OnOverInit();
int OnOverInput();
int OnOverProcess();
int OnOverRender();

StageType CurrentStageType;

bool StageInit()
{
	AddStage(Title);
	AddStage(Game);
	AddStage(Win);
	AddStage(Over);

	return true;
}

bool SetStage(StageType type)
{
	if (type == StageType::STAGE_TYPE_COUNT)
	{
		return false;
	}

	CurrentStageType = type;
    return _initHandler[(int)CurrentStageType]();
}

int StageInput()
{
	_inputHandler[(int)CurrentStageType]();
	return 0;
}

int StageProcess()
{
	_processHandler[(int)CurrentStageType]();
	return 0;
}

int StageRender()
{
	_renderHandler[(int)CurrentStageType]();
	return 0;
}










// Title //
bool OnTitleInit()
{
	return true;
}

int OnTitleInput()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
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

	CopyDataToRendBuffer({ 13, 6 }, "Press To Space");

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
	return 0;
}




// Win
bool OnWinInit()
{
	return true;
}

int OnWinInput()
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

int OnWinProcess()
{
	return 0;
}

int OnWinRender()
{
	CopyDataToRendBuffer({ 13, 2 }, "~~ WIN ~~");
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
