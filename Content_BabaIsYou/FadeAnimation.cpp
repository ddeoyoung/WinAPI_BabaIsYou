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

		GameEngineRenderer* FadeRender = CreateRenderer("FadeAnimation.bmp", RenderOrder::PlayUI);

		FadeRender->CreateAnimation("FadeUI", "FadeAnimation.bmp", 34, 0, 0.01f, false);
		FadeRender->ChangeAnimation("FadeUI");
		FadeRender->SetRenderScaleToTexture();

		float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
		FadeRender->SetRenderPos(WinScale);

	}
}


void FadeAnimation::Update(float _Delta)
{

}
void FadeAnimation::Render()
{

}
void FadeAnimation::Release()
{

}