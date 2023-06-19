#include "ContentCore.h"
#include "LogoLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "StageTitleLevel.h"
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
	GameEngineCore::CreateLevel<StageTitleLevel>("StageTitleLevel"); // 스테이지 타이틀
	GameEngineCore::CreateLevel<PuzzleLevel>("PuzzleLevel"); // 퍼즐

	GameEngineCore::ChangeLevel("LogoLevel");
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