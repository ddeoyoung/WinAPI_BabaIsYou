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
		FadeUI->FadeOut();

		//if (nullptr != FadeUI && true == FadeUI->IsAnimationEnd)
		//{
		//	GameEngineCore::ChangeLevel("TitleLevel");
		//}

		if (true == FadeUI->CheckAnimationEnd())
		{
			GameEngineCore::ChangeLevel("TitleLevel");
		}
	}
}
