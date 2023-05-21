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

		FadeRender->CreateAnimation("FadeUI", "FadeAnimation.bmp", 0, 34, 0.03f, true);
		FadeRender->ChangeAnimation("FadeUI");
		FadeRender->SetRenderScaleToTexture();

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