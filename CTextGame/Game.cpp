#include "Game.h"

#include "File.h"

#include "Grid.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "UIRenderer.h"


STAGE_FILE_INFO _stage[MAX_STAGE_COUNT];
MONSTER_FILE_INFO _monsterInfo[MAX_MONSTER_TYPE];

int CurrentStage = 0;

void CreateStage(int stage);

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
	UIRender();
	return 0;
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

void CreateStage(int stage)
{
	// Monster ����
	for (const auto& stageMonsterInfo : _stage[stage].MonsterInfos)
	{
		if (stageMonsterInfo.isVailed == false)
		{
			break;
		}

		CreateMonster(_monsterInfo[stageMonsterInfo.Id], stageMonsterInfo);
	}

	// Player ����
	LoadPlayerData(&_stage[stage]);
}

void NetGameStage()
{
	SetGameStage(CurrentStage + 1);
}

