#include "CongratsUI.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include "ContentsEnum.h"

#include "FadeAnimation.h"

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

	if (false == ResourcesManager::GetInst().IsLoadTexture("Congratulations.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Puzzle\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Congratulations.bmp"), 1, 9);
	}

	WinScale = GameEngineWindow::MainWindow.GetScale().Half();

	CongratsRender = CreateRenderer("CongratulationsUI.bmp", RENDER_ORDER::CONGRATS);
	CongratsRender->SetRenderPos(WinScale);
	CongratsRender->SetRenderScaleToTexture();

	// 축하메세지 나타나기
	CongratsRender->CreateAnimation("Congrats", "CongratulationsUI.bmp", 0, 36, 0.035f, false);

	// 축하메세지 유지
	CongratsRender->CreateAnimation("CongratsCont", "Congratulations.bmp", 0, 8, 0.15f, false);
}

void CongratsUI::Update(float _Delta)
{

}

void CongratsUI::SetCongratsAnimation()
{
	CongratsRender->ChangeAnimation("Congrats");
}
