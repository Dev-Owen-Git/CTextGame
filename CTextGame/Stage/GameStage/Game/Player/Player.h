#pragma once

#include <File/File.h>
#include <Stage/GameStage/Game/Entity/Entity.h>

struct PLAYER
{
	ENTITY Entity;

	unsigned int LastFireTime;
	unsigned int FireCoolTime;
};

extern PLAYER Player;

bool PlayerInit();

int PlayerInput();
int PlayerPorcess();
int PlayerRender();

void OnPlayerDead(ENTITY* const entity);

void LoadPlayerData(const STAGE_FILE_INFO& stageData);