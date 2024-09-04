#pragma once

#include <Stage/GameStage/Game/Entity/Entity.h>
#include "File/File.h"

extern unsigned int AliveMonsterCount;

struct MONSTER
{
	ENTITY Entity;

	unsigned char Sprite;

	unsigned int LastFireTime;
	unsigned int FireCoolTime;
	unsigned int FireCoolTimeRange;

	unsigned int MoveType;

	vector2D<double> MoveDir = { 0, 0 };
};



bool MonsterInit();
int MonsterProcess();
int MonsterRender();

void OnMonsterDead(ENTITY* const entity);
bool CreateMonster(const MONSTER_FILE_INFO&   monsterInfo, const STAGE_MONSTER_INFO&  stageMonsterInfo);
void ClearAllMonsters();

MONSTER* GetUnValiedMonster();