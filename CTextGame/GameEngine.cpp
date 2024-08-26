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

    return SetStage(StageType::Title);
}

int GameEngineStart()
{
    while (true)
    {
        //// Sleep �Լ� �ϰ� �ִ��� 50FPS�� ���߱�
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

       /* StateInput();
        StateProcess();
        StateRender();
        WaitforFrame();*/
    }

    return 0;
}
