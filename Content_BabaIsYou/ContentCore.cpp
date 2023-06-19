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

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel"); // �ΰ�
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel"); // Ÿ��Ʋ
	GameEngineCore::CreateLevel<WorldMapLevel>("WorldMapLevel"); // �����
	GameEngineCore::CreateLevel<StageTitleLevel>("StageTitleLevel"); // �������� Ÿ��Ʋ
	GameEngineCore::CreateLevel<PuzzleLevel>("PuzzleLevel"); // ����

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