#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Background_Black.h"
#include "TitleLogo.h"
#include "FadeAnimation.h"
#include "Button.h"


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	// Background
	BackgroundUI = CreateActor<Background_Black>();
	BackgroundUI->Init("Background_Black.bmp", { 1280, 720 });

	// Title Logo
	TitleLogoUI = CreateActor<TitleLogo>();

	// Title Button
	StartButton = CreateActor<Button>();
	StartButton->SetButton("StartButton.bmp");
	StartButton->SetPos({ 640, 450 });

	// Button Collision
	StartButton->Collision = StartButton->CreateCollision();
	StartButton->Collision->SetCollisionScale(StartButton->GetScale());



	// Fade Animation
	FadeUI = CreateActor<FadeAnimation>();
	FadeUI->FadeIn();

}
void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		FadeUI->FadeOut();
	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeOut")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		GameEngineCore::ChangeLevel("WorldMapLevel");
	}
}

