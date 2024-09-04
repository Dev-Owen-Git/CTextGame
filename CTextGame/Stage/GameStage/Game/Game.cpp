#include "Game.h"

#include <File/File.h>

#include <Stage/GameStage/Game/Grid/Grid.h>
#include <Stage/GameStage/Game/Bullet/Bullet.h>
#include <Stage/GameStage/Game/Player/Player.h>
#include <Stage/GameStage/Game/Monster/Monster.h>
#include <Stage/GameStage/Game/Ui/GameUIRenderer.h>

#include <Stage/Stage.h>


STAGE_FILE_INFO		_stage[MAX_STAGE_COUNT];
MONSTER_FILE_INFO	_monsterInfo[MAX_MONSTER_TYPE];
bool _isLoadStageFile = false;

int CurrentStage = 0;

void CreateStage(int stage);

bool GameInit()
{
	// 파일이 불러와있는지 확인
	if (_isLoadStageFile == false)
	{
		LoadStageFiles(_stage);
		LoadMonsterFiles(_monsterInfo);

		_isLoadStageFile = true;
	}

	if (GridInit() == false)
	{
		return false;
	}

	if (BulletInit() == false)
	{
		return false;
	}

	if (MonsterInit() == false)
	{
		return false;
	}

	if (PlayerInit() == false)
	{
		return false;
	}

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
		SetStage(StageType::Win);
		return;
	}

	CurrentStage = stage;

	CreateStage(CurrentStage);
}

void NextGameStage()
{
	SetGameStage(CurrentStage + 1);
}


void CreateStage(int stage)
{
	BulletInit();

	// Monster 생성
	for (const auto& stageMonsterInfo : _stage[stage].MonsterInfos)
	{
		if (stageMonsterInfo.isVailed == false)
		{
			break;
		}

		CreateMonster(_monsterInfo[stageMonsterInfo.Id], stageMonsterInfo);
	}

	// Player 생성
	LoadPlayerData(_stage[stage]);
}