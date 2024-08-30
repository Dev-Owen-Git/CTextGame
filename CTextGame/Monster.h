#pragma once

#include "Entity.h"
#include "File.h"
#include "Bullet.h"

extern unsigned int AliveMonsterCount;

bool CreateMonster(const MONSTER_FILE_INFO& const  monsterInfo, const STAGE_MONSTER_INFO& const stageMonsterInfo);
void ClearAllMonsters();

bool MonsterInit();

int MonsterProcess();
int MonsterRender();

void MonsterHit(ENTITY* const entity, const Bullet* const bullet, const int damage);

MONSTER* GetUnValiedMonster();