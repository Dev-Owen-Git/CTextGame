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
        //frame
        ProcessFrame();

        // frame Test
        if (GetAsyncKeyState(VK_F1))
        {
            Sleep(1000);
        }

        // Process
        StateInput();
        StateProcess();

        if (FrameSkip() == false)
        {
            RenderFrame();
            StateRender();

            // BUFFER �׸���
            DrawBuffer();
        }

        // Wait
        WaitforFrame();
    }

    return 0;
}
