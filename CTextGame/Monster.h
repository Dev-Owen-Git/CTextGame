#pragma once

#include "Entity.h"
#include "File.h"
#include "Bullet.h"

extern unsigned int AliveMonsterCount;



bool MonsterInit();
int MonsterProcess();
int MonsterRender();

void MonsterHit(ENTITY* const entity, const int damage);
bool CreateMonster(const MONSTER_FILE_INFO&   monsterInfo, const STAGE_MONSTER_INFO&  stageMonsterInfo);
void ClearAllMonsters();

MONSTER* GetUnValiedMonster();