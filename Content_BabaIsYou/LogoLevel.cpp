#include "LogoLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
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

	// FadeUI->InAnimationEnd == true 일 때 P를 누르면 ChangeLevel

	if (true == GameEngineInput::IsDown('P'))
	{
		FadeAnimation* FadeUI = CreateActor<FadeAnimation>();
		//GameEngineCore::ChangeLevel("TitleLevel");
	}
}
void LogoLevel::Render()
{

}
void LogoLevel::Release()
{

}