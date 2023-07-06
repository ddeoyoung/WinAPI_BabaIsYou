#include "LogoLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
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

	if (nullptr == GameEngineSound::FindSound("title.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\BGM\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("title.ogg"));
	}
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

void LogoLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	
}

void LogoLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	//BGMPlayer.Stop();
}