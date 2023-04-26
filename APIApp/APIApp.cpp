
#include <Windows.h>
#include <GameEnginePlatform/GameEngineWindow.h>

void TestStart(HINSTANCE _Inst)
{
    GameEngineWindow::MainWindow.Open("MainWindow", _Inst);
}

void TestEnd()
{

}

void TestUpdate()
{

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // CallBack ¹æ½Ä
    GameEngineWindow::MessageLoop(hInstance, TestStart, TestUpdate, TestEnd);
    return 0;
}

