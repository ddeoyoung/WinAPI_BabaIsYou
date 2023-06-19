#include "FadeAnimation.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
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
	}

	FadeRender = CreateRenderer("FadeAnimation.bmp", RenderOrder::Fade);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	FadeRender->SetRenderPos(WinScale);
	FadeRender->SetRenderScaleToTexture();

	FadeRender->CreateAnimation("FadeOut", "FadeAnimation.bmp", 0, 34, 0.015f, false);
	FadeRender->CreateAnimation("FadeIn", "FadeAnimation.bmp", 34, 0, 0.015f, false);
}

// 사라지는 애니메이션 (레벨 전환 전)
void FadeAnimation::FadeOut()
{
	FadeRender->ChangeAnimation("FadeOut");
}

// 나타나는 애니메이션 (레벨 전환 후) 
void FadeAnimation::FadeIn()
{
	FadeRender->ChangeAnimation("FadeIn");
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