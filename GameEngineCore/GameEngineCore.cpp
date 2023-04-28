#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineLevel.h"

std::string GameEngineCore::WindowTitle = "";
std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;
GameEngineLevel* GameEngineCore::CurLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;


GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	// 엔진쪽에 준비를 다 해고
	GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);

	// 유저의 준비를 해준다.
	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	CurLevel->Update();
	CurLevel->ActorUpdate();
	CurLevel->Render();
	CurLevel->ActorRender();

}

void GameEngineCore::CoreEnd()
{
	if (nullptr != NextLevel)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	CurLevel->Update();
	CurLevel->ActorUpdate();
	CurLevel->Render();
	CurLevel->ActorRender();
}

void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
	GameEngineDebug::LeckCheck();

	Process = _Ptr;
	WindowTitle = _Title;
	GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}


void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}