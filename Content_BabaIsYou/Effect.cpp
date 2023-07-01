#include "Effect.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
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

}