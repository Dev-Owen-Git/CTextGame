#include "GameStage.h"
#include "Renderer.h"
#include "Game.h"

#include <Windows.h>

// COMMON //

bool(*initHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*inputHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*processHandler[(int)StageType::STAGE_TYPE_COUNT])();
int(*renderHandler[(int)StageType::STAGE_TYPE_COUNT])();

StageType currentStageType;

bool StageInit()
{
	initHandler[(int)StageType::TITLE]		= TitleInit;
	inputHandler[(int)StageType::TITLE]		= TitleInput;
	processHandler[(int)StageType::TITLE]	= TitleProcess;
	renderHandler[(int)StageType::TITLE]	= TitleRender;

	initHandler[(int)StageType::GAME]		= GameInit;
	inputHandler[(int)StageType::GAME]		= GameInput;
	processHandler[(int)StageType::GAME]	= GameProcess;
	renderHandler[(int)StageType::GAME]		= GameRender;

	initHandler[(int)StageType::OVER]		= OverInit;
	inputHandler[(int)StageType::OVER]		= OverInput;
	processHandler[(int)StageType::OVER]	= OverProcess;
	renderHandler[(int)StageType::OVER]		= OverRender;

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

int StateInput()
{
	inputHandler[(int)currentStageType]();
	return 0;
}

int StateProcess()
{
	processHandler[(int)currentStageType]();
	return 0;
}

int StateRender()
{
	renderHandler[(int)currentStageType]();
	DrawBuffer();

	return 0;
}










// Title //
bool TitleInit()
{
	return true;
}

int TitleInput()
{
	return 0;
}

int TitleProcess()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (SetStage(StageType::GAME) == false)
		{
			__debugbreak();
		}
		return 0;
	}

	return 0;
}

int TitleRender()
{	
	CopyDataToRendBuffer({ 13, 2 }, "Shooting Game");

	CopyDataToRendBuffer({ 12, 5 }, "------------");

	CopyDataToRendBuffer({ 14, 6 }, "1. Game");

	CopyDataToRendBuffer({ 12, 7 }, "------------");

	return 0;
}










// Game ///
bool GameInit()
{
	// TODO 몬스터 정보 불러오기
	LoadPlayerData();
	LoadMonsterData();
	

	return true;
}

int GameInput()
{
	PlayerInput();


	return 0;
}

int GameProcess()
{
	PlayerPorcess();
	BulletProcess();
	return 0;
}

int GameRender()
{
	PlayerRender();
	BulletRender();
	return 0;
}






// OVER //

bool OverInit()
{
	return true;
}

int OverInput()
{
	return 0;
}

int OverProcess()
{
	return 0;
}

int OverRender()
{
	return 0;
}
