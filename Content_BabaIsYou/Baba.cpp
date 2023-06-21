#include "Baba.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>


Baba::Baba()
{
}

Baba::~Baba()
{
}

void Baba::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Actor.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Actor.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Actor.bmp", 24, 40);
	}

	BabaRenderer = CreateRenderer("Actor.bmp", RENDER_ORDER::PLAY);
	BabaRenderer->CreateAnimationToFrame("Baba_Left", "Actor.bmp", {10, 34, 58}, 0.2f, true);
}

void Baba::Update(float _Delta)
{

}

void Baba::StateUpdate(float _Delta)
{
	switch (Dir)
	{
	case BABA_DIR::LEFT:
		return;
	case BABA_DIR::RIGHT:
		return;
	case BABA_DIR::UP:
		return;
	case BABA_DIR::DOWN:
		return;
	default:
		break;
	}
}