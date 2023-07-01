#include "Effect.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include "ContentsEnum.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Effect.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Effect.bmp"), 7, 44);
	}

	EffectRender = CreateRenderer("Effect.bmp", RENDER_ORDER::PLAY_UI);
	EffectRender->SetRenderScaleToTexture();

	Dir.X = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	Dir.Y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);

	Dir.Normalize();

	EffectRender->CreateAnimation("FLAG_WIN", "Effect.bmp", 231, 237, 0.1f, false);

	Speed = 80.f;
}


void Effect::Update(float _Delta)
{
	AddPos(Dir * Speed * _Delta);

	if (true == EffectRender->IsAnimationEnd())
	{
		Death();
		return;
	}
}