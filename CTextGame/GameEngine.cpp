#include "GameEngine.h"

#include "GameStage.h"
#include <Windows.h>
#include "Renderer.h"
#include "FrameRate.h"

bool GameEngineInit()
{
    InitFrameRate(50);

    StageInit();
    RendererInit();

    return SetStage(StageType::Title);
}

int GameEngineStart()
{
    while (true)
    {
        // frame
        ProcessFrame();
        RenderFrame();

        // Process
        StateInput();
        StateProcess();
        StateRender();

        // BUFFER ±×¸®±â
        DrawBuffer();

        // Wait
        WaitforFrame();
    }

    return 0;
}
