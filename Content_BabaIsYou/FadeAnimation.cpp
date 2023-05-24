#include "FadeAnimation.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"

FadeAnimation::FadeAnimation()
{
}

FadeAnimation::~FadeAnimation()
{
}

void FadeAnimation::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("FadeAnimation.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FadeAnimation.bmp"), 1, 35);

		FadeRender = CreateRenderer("FadeAnimation.bmp", RenderOrder::PlayUI);

		FadeRender->CreateAnimation("FadeUI", "FadeAnimation.bmp", 0, 34, 0.01f, false);
		FadeRender->ChangeAnimation("FadeUI");
		FadeRender->SetRenderScaleToTexture();

		float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
		FadeRender->SetRenderPos(WinScale);
	}

	
}


void FadeAnimation::Update(float _Delta)
{
	if (true == FadeRender->IsAnimationEnd())
	{
		IsAnimationEnd = true;
	}
}


bool FadeAnimation::CheckAnimationEnd()
{
	return FadeRender->IsAnimationEnd();
}