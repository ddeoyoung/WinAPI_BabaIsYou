#include "ContentCore.h"
#include "LogoLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "TutorialLevel.h"
#include "PuzzleLevel1.h"
#include "PuzzleLevel2.h"
#include "PuzzleLevel3.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });
	GameEngineSound::SetGlobalVolume(30.f);

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<WorldMapLevel>("WorldMapLevel");
	GameEngineCore::CreateLevel<TutorialLevel>("TutorialLevel");
	GameEngineCore::CreateLevel<PuzzleLevel1>("PuzzleLevel1");
	GameEngineCore::CreateLevel<PuzzleLevel2>("PuzzleLevel2");
	GameEngineCore::CreateLevel<PuzzleLevel3>("PuzzleLevel3");

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