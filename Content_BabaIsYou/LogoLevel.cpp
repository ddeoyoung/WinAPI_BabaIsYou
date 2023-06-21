#include "LogoLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Logo.h"
#include "Background_Black.h"
#include "FadeAnimation.h"


LogoLevel::LogoLevel()
{

}

LogoLevel::~LogoLevel()
{

}

void LogoLevel::Start()
{
	BackgroundUI = CreateActor<Background_Black>();
	BackgroundUI->Init("Background_Black.bmp", {1280, 720});
	LogoUI = CreateActor<Logo>();
	FadeUI = CreateActor<FadeAnimation>();
	FadeUI->FadeIn();
}

void LogoLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		FadeUI->On();
		FadeUI->FadeOut();
	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeIn")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		FadeUI->Off();
	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeOut")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
}
