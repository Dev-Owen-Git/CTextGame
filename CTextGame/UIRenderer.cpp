#include "UIRenderer.h"

#include "Player.h"
#include "Monster.h"
#include "Renderer.h"
#include "Game.h"

#include <stdio.h>

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
