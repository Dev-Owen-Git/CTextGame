#include "GameStage.h"

bool GameStage::SetStage(StageType type)
{
	switch (type)
	{
	case GameStage::StageType::TITLE:
		break;
	case GameStage::StageType::GAME:
		break;
	case GameStage::StageType::OVER:
		break;
	default:
		break;
	}

    return true;
}
