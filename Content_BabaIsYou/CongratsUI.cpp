#include "CongratsUI.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include "ContentsEnum.h"

CongratsUI::CongratsUI()
{
}

CongratsUI::~CongratsUI()
{
}

void CongratsUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("CongratulationsUI.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Puzzle\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("CongratulationsUI.bmp"), 1, 37);
	}

	FadeRender = CreateRenderer("CongratulationsUI.bmp", RENDER_ORDER::CONGRATS);
	
	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	FadeRender->SetRenderPos(WinScale);
	FadeRender->SetRenderScaleToTexture();

	FadeRender->CreateAnimation("Congrats", "CongratulationsUI.bmp", 0, 36, 0.02f, false);
}

void CongratsUI::Update(float _Delta)
{

}

void CongratsUI::SetCongratsAnimation()
{
	FadeRender->ChangeAnimation("Congrats");
}