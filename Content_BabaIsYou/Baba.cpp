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
	BabaRenderer->CreateAnimationToFrame("Baba_Left", "Actor.bmp", { 10, 34, 58 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Right", "Actor.bmp", { 2, 26, 50 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Up", "Actor.bmp", { 6, 30, 54 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Down", "Actor.bmp", { 14, 38, 62 }, 0.2f, true);

	BabaRenderer->CreateAnimationToFrame("Baba_Left2", "Actor.bmp", { 11, 35, 59 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Right2", "Actor.bmp", { 3, 27, 51 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Up2", "Actor.bmp", { 7, 31, 55 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Down2", "Actor.bmp", { 15, 39, 63 }, 0.2f, true);

	BabaRenderer->CreateAnimationToFrame("Baba_Left3", "Actor.bmp", { 12, 36, 60 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Right3", "Actor.bmp", { 4, 28, 52 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Up3", "Actor.bmp", { 8, 32, 56 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Down3", "Actor.bmp", { 16, 40, 64 }, 0.2f, true);

	BabaRenderer->CreateAnimationToFrame("Baba_Left4", "Actor.bmp", { 13, 37, 61 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Right4", "Actor.bmp", { 5, 29, 53 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Up4", "Actor.bmp", { 9, 33, 57 }, 0.2f, true);
	BabaRenderer->CreateAnimationToFrame("Baba_Down4", "Actor.bmp", { 17, 41, 65 }, 0.2f, true);

	BabaRenderer->ChangeAnimation("Baba_Left");
	BabaRenderer->SetRenderScale({40, 40});
}


void Baba::Update(float _Delta)
{
	CheckDir();
	ChangeAnimationState(Dir);
}


void Baba::CheckDir()
{
	if (true == GameEngineInput::IsDown('D'))
	{
		Dir = BABA_DIR::RIGHT;
		return;
	}

	else if (true == GameEngineInput::IsDown('W'))
	{
		Dir = BABA_DIR::UP;
		return;
	}

	else if (true == GameEngineInput::IsDown('A'))
	{
		Dir = BABA_DIR::LEFT;
		return;
	}

	else if (true == GameEngineInput::IsDown('S'))
	{
		Dir = BABA_DIR::DOWN;
		return;
	}
}


void Baba::ChangeAnimationState(BABA_DIR _Dir)
{
	Dir = _Dir;

	switch (Dir)
	{
	case BABA_DIR::LEFT:
		AnimationName = "Baba_Left";
		break;
	case BABA_DIR::RIGHT:
		AnimationName = "Baba_Right";
		break;
	case BABA_DIR::UP:
		AnimationName = "Baba_Up";
		break;
	case BABA_DIR::DOWN:
		AnimationName = "Baba_Down";
		break;
	default:
		break;
	}

	BabaRenderer->ChangeAnimation(AnimationName);
}