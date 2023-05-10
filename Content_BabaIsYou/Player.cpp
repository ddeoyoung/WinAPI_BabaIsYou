#include "Player.h"
#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	// Texture Load
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");


		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}


	{
		GameEngineRenderer* Ptr = CreateRenderer("Test.Bmp", RenderOrder::Play);
		Ptr->SetRenderScale({ 200, 200 });
		Ptr->SetTexture("Test.Bmp");
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 0, -100 });
		Ptr->SetRenderScale({ 200, 40 });
		Ptr->SetTexture("HPBar.bmp");
	}


	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	// GetLevel()->GetMainCamera()->SetPos({ -WinScale.hX(), -WinScale.hY() });

	SetPos(WinScale.Half());
}

void Player::Update(float _Delta)
{
	// Player->GetPos() == Monster->GetPos();
	// float Time = GameEngineTime::MainTimer.GetDeltaTime();
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (0 != GetAsyncKeyState('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (0 != GetAsyncKeyState('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);

}

void Player::Render()
{

}

void Player::Release()
{
}