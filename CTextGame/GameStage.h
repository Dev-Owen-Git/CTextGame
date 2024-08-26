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

int StateInput();
int StateProcess();
int StateRender();

bool TitleInit();
int TitleInput();
int TitleProcess();
int TitleRender();

bool GameInit();
int GameInput();
int GameProcess();
int GameRender();

bool OverInit();
int OverInput();
int OverProcess();
int OverRender();

extern bool(*initHandler [(int)StageType::STAGE_TYPE_COUNT] )();
extern int(*inputHandler[(int)StageType::STAGE_TYPE_COUNT])();
extern int(*processHandler[(int)StageType::STAGE_TYPE_COUNT])();
extern int(*renderHandler[(int)StageType::STAGE_TYPE_COUNT])();

extern StageType currentStageType;