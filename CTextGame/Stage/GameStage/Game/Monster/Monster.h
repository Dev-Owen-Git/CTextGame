#pragma once

#include <Stage/GameStage/Game/Entity/Entity.h>
#include "File/File.h"

extern unsigned int AliveMonsterCount;



bool MonsterInit();
int MonsterProcess();
int MonsterRender();

void MonsterHit(ENTITY* const entity, const int damage);
bool CreateMonster(const MONSTER_FILE_INFO&   monsterInfo, const STAGE_MONSTER_INFO&  stageMonsterInfo);
void ClearAllMonsters();

MONSTER* GetUnValiedMonster();