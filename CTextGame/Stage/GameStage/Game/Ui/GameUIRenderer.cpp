#include "GameUIRenderer.h"

#include <Stage/GameStage/Game/Player/Player.h>
#include <Stage/GameStage/Game/Monster/Monster.h>
#include <Stage/GameStage/Game/Game.h>
#include <Renderer/Renderer.h>

#include <cstdio>

void UIRender()
{
    char buffer[100];

    sprintf_s(buffer, "Current Stage : %d", CurrentStage + 1);
    CopyDataToRendBuffer({ 45, 3 }, buffer);

    sprintf_s(buffer, "Player HP : %d", Player.Entity.Hp);
    CopyDataToRendBuffer({ 45, 5 }, buffer);

    sprintf_s(buffer, "Alive Monster Count : %d", AliveMonsterCount);
    CopyDataToRendBuffer({ 45, 6 }, buffer);
}
