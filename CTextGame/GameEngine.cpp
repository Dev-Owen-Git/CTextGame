#include "GameEngine.h"

#include "GameStage.h"

bool GameEngine::Init()
{
    return GameStage::SetStage(GameStage::StageType::TITLE);
}

int GameEngine::Start()
{
    return 0;
}
