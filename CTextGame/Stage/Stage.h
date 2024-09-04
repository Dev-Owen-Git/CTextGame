#pragma once

enum class StageType
{
	Title,
	Game,
	Win,
	Over,
	STAGE_TYPE_COUNT
};

bool StageInit();
bool SetStage(StageType type);

int StageInput();
int StageProcess();
int StageRender();

extern StageType CurrentStageType;