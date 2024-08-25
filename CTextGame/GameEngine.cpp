#include "GameEngine.h"

#include "GameStage.h"
#include <Windows.h>
#include "Renderer.h"
#include "FrameRate.h"

bool GameEngineInit()
{
    InitFrameRate(30);

    StageInit();
    RendererInit();

    return SetStage(StageType::TITLE);
}

int GameEngineStart()
{
    while (true)
    {
        if ( CheckForFrame() == true )
        {
            StateInput();
            StateProcess();
            StateRender();
        }
        else
        {
            UpdateFrame();
        }
    }

    return 0;
}
