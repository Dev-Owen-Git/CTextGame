#include "Game.h"

#include "File.h"

#include "Grid.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Stage.h"

STAGE_FILE_INFO _stage[MAX_STAGE_COUNT];
MONSTER_FILE_INFO _monsterInfo[MAX_MONSTER_TYPE];

int CurrentStage = 0;

bool GameInit()
{
	if (_stage[0].isVailed == false)
	{
		LoadStageFiles(_stage);
		LoadMonsterFiles(_monsterInfo);
	}

	GridInit();
	BulletInit();
	MonsterInit();

	SetGameStage(0);
	return true;
}

int GameInput()
{
	PlayerInput();
	return 0;
}

int GameProcess()
{
	BulletProcess();
	PlayerPorcess();
	MonsterProcess();
	return 0;
}

int GameRender()
{
	BulletRender();
	PlayerRender();
	MonsterRender();
	return 0;
}

void CreateStage(int stage)
{
	// Monster 持失
	for (const auto& stageMonsterInfo : _stage[stage].MonsterInfos)
	{
		if (stageMonsterInfo.isVailed == false)
		{
			break;
		}

		CreateMonster(_monsterInfo[stageMonsterInfo.Id], stageMonsterInfo);
	}

	// Player 持失
	LoadPlayerData(&_stage[stage]);
}

void SetGameStage(const  int stage)
{
	if (_stage[stage].isVailed == false)
	{
		return;
	}

	CurrentStage = stage;

	CreateStage(CurrentStage);
}

void NetGameStage()
{
	SetGameStage(CurrentStage + 1);
}

