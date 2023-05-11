
#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>
#include <Content_BabaIsYou/ContentCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    GameEngineCore::EngineStart<ContentCore>("Baba Is You", hInstance);

    return 0;
}

  