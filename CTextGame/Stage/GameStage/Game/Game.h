#pragma once

extern int CurrentStage;

// Game
bool GameInit();

int GameInput();
int GameProcess();
int GameRender();

void SetGameStage(const int stage);

void NetGameStage();