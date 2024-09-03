#pragma once

#include <Stage/GameStage/Game/Entity/Entity.h>
#include "File/File.h"

extern PLAYER Player;

bool PlayerInit();

int PlayerInput();
int PlayerPorcess();
int PlayerRender();

void PlayerHit(ENTITY* const entity, const int damage);

void LoadPlayerData(const STAGE_FILE_INFO* stageData);