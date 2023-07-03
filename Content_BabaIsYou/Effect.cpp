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
	EffectRender->CreateAnimation("FLAG_WIN", "Effect.bmp", 231, 237, 0.1f, false);
	EffectRender->CreateAnimation("BABA_WALK", "Effect.bmp", 0, 6, 0.1f, false);
	EffectRender->CreateAnimation("WALL_WALK", "Effect.bmp", 56, 62, 0.1f, false);

	Dir.X = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	Dir.Y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	Dir.Normalize();
}


void Effect::Update(float _Delta)
{
	// 승리 타일 이펙트
	if (true == EffectRender->IsAnimation("FLAG_WIN"))
	{
		Speed = 80.f;
		AddPos(Dir * Speed * _Delta);
	}

	// 플레이어 타일 발자국 이펙트
	if (true == EffectRender->IsAnimation("BABA_WALK"))
	{
		Speed = 50.f;
		AddPos(Dir * Speed * _Delta * 0.5);
	}

	if (true == EffectRender->IsAnimation("WALL_WALK"))
	{
		Speed = 50.f;
		AddPos(Dir * Speed * _Delta * 0.5);
	}

	if (true == EffectRender->IsAnimationEnd())
	{
		Death();
		return;
	}
}