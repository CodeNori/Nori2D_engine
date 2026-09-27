// NoriRendererTest.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "DxVars.h"
#include "DemoGame.h"


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.



bool Load_Game_JSON();



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    srand(time(nullptr));
    dw1::init_DebugString();

    Load_Game_JSON();

    g_Dx11.hInstance = hInstance;
    g_Dx11.titleBarStats = true;
    g_Dx11.titleBarText = "Nori2D";
    g_Dx11.dxFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1;

    {
        Scriptor scriptor;
        scriptor.doFile("Content\\game.lua");
    }

    if (g_Dx11.OpenWindow2D())
    {
        g_Dx11.game = new DemoGame;
        //g_Dx11.window->setBackgroundColor(0.f, 0.f, 1.f);
        
        g_Dx11.Run();
        
        SAFE_DELETE(g_Dx11.game);
    }
    g_Dx11.CloseWindow2D();

    dw1::destroy_DebugString();
    return 0;
}


bool Load_Game_JSON()
{
    dw1::JsonFile2 jsonfile("Content\\Game.json");

    g_Dx11.width = int(jsonfile["DxWindow"]["screenWidth"]);
    g_Dx11.height = int(jsonfile["DxWindow"]["screenHeight"]);
    // g_Dx11.titleBarText = (char*)(jsonfile["DxWindow"]["title"]);

    return false;
}