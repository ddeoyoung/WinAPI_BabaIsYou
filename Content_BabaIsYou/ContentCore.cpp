#include "ContentCore.h"
#include "LogoLevel.h"
#include "TitleLevel.h"
#include "WorldMapLevel.h"
#include "TutorialLevel.h"
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

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel"); // �ΰ�
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel"); // Ÿ��Ʋ
	GameEngineCore::CreateLevel<WorldMapLevel>("WorldMapLevel"); // �����
	GameEngineCore::CreateLevel<TutorialLevel>("TutorialLevel"); // �������� 0
	GameEngineCore::CreateLevel<PuzzleLevel>("PuzzleLevel"); // �������� 1

	GameEngineCore::ChangeLevel("TutorialLevel");
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