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

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel"); // ·Î°í
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel"); // Å¸ÀÌÆ²
	GameEngineCore::CreateLevel<WorldMapLevel>("WorldMapLevel"); // ¿ùµå¸Ê
	GameEngineCore::CreateLevel<PuzzleLevel>("PuzzleLevel"); // ÆÛÁñ

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