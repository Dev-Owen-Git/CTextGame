#pragma once

#include "Entity.h"
#include "File.h"

extern PLAYER Player;

bool PlayerInit();

int PlayerInput();
int PlayerPorcess();
int PlayerRender();

void PlayerHit(ENTITY* const entity, const int damage);

void LoadPlayerData(const STAGE_FILE_INFO* stageData);