#include "GameStage.h"
#include "Renderer.h"
#include "File.h"
#include "Game.h"

#include <Windows.h>

// COMMON //

#define AddStage(stgaeName) \
	initHandler[(int)StageType::##stgaeName]		= ##stgaeName##Init;		\
	inputHandler[(int)StageType::##stgaeName]		= ##stgaeName##Input;		\
	processHandler[(int)StageType::##stgaeName]		= ##stgaeName##Process;		\
	renderHandler[(int)StageType::##stgaeName]		= ##stgaeName##Render

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
		if (SetStage(StageType::Game) == false)
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
const int MAX_STAGE_COUNT = 100;

struct StageInfo
{
	bool InVailed = false;

	Enitiy		Monsters[MAX_MONSTER_COUNT];
	uvector2	PlayerSpawnPoint;
};

StageInfo _stage[MAX_STAGE_COUNT];

bool GameInit()
{
	// TODO 몬스터 정보 불러오기
	LoadStage(&_stage, sizeof(StageInfo));
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
