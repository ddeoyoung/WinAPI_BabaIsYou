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
	Background_Black* Back = CreateActor<Background_Black>();
	Logo* LogoUI = CreateActor<Logo>();
}

void LogoLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		FadeUI->FadeOut();
	}
}
