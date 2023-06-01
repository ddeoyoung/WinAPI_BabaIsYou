#include "ContentCore.h"
#include "LogoLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "PuzzleLevel.h"
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
	GameEngineCore::CreateLevel<WorldMapLevel>("WorldMapLevel"); // 월드맵
	GameEngineCore::CreateLevel<PuzzleLevel>("PuzzleLevel"); // 월드맵

	GameEngineCore::ChangeLevel("WorldMapLevel");
}

void ContentCore::Update(float _Delta)
{
}

void ContentCore::Render(float _Delta)
{
}

void ContentCore::Release()
{
}