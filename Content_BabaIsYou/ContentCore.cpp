#include "ContentCore.h"
#include "LogoLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel"); // 로고
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel"); // 타이틀
	GameEngineCore::CreateLevel<WorldMapLevel>("WorldMapLevel"); // 스테이지 선택

	GameEngineCore::ChangeLevel("LogoLevel");
}

void ContentCore::Update(float _Delta)
{
}

void ContentCore::Render()
{
}

void ContentCore::Release()
{
}