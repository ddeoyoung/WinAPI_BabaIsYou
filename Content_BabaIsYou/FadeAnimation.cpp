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

		float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
		FadeRender->SetRenderPos(WinScale);
	}
}

// 레벨 전환 전
void FadeAnimation::FadeOut()
{
	GameEngineWindowTexture* FadeOutUI = ResourcesManager::GetInst().FindTexture("FadeAnimation.bmp");
	FadeRender->CreateAnimation("FadeOut", "FadeAnimation.bmp", 0, 34, 0.01f, false);
	FadeRender->ChangeAnimation("FadeOut");
	FadeRender->SetRenderScaleToTexture();
}

// 레벨 전환 후
void FadeAnimation::FadeIn()
{
	GameEngineWindowTexture* FadeInUI = ResourcesManager::GetInst().FindTexture("FadeAnimation.bmp");
	FadeRender->CreateAnimation("FadeIn", "FadeAnimation.bmp", 34, 0, 0.01f, false);
	FadeRender->ChangeAnimation("FadeIn");
	FadeRender->SetRenderScaleToTexture();
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