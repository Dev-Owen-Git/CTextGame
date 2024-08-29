#pragma once

enum class StageType
{
	Title,
	Game,
	Over,
	STAGE_TYPE_COUNT
};

bool StageInit();
bool SetStage(StageType type);

int StageInput();
int StageProcess();
int StageRender();

bool OnTitleInit();
int OnTitleInput();
int OnTitleProcess();
int OnTitleRender();

bool OnGameInit();
int OnGameInput();
int OnGameProcess();
int OnGameRender();

bool OnOverInit();
int OnOverInput();
int OnOverProcess();
int OnOverRender();

extern bool(*initHandler [(int)StageType::STAGE_TYPE_COUNT] )();
extern int(*inputHandler[(int)StageType::STAGE_TYPE_COUNT])();
extern int(*processHandler[(int)StageType::STAGE_TYPE_COUNT])();
extern int(*renderHandler[(int)StageType::STAGE_TYPE_COUNT])();

extern StageType currentStageType;