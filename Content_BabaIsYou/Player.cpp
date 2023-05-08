#include "Player.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/ResourcesManager.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	// Texture Load
	if (false == ResourcesManager::GetInst().IsLoadTexture("Player_Idle.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Test.Bmp");

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void Player::Update(float _Delta)
{
	// float Time = GameEngineTime::MainTimer.GetDeltaTime();
	
	AddPos({ 100.0f * _Delta, 0.0f });
}

void Player::Render()
{
	//SetPos({ 200, 200 });
	//SetScale({ 100, 100 });

	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();
	GameEngineTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Test.Bmp");
	HDC ImageDC = FindTexture->GetImageDC();

	BitBlt(WindowDC, 100, 100, 500, 500, ImageDC, 0, 0, SRCCOPY);

	//Rectangle(WindowDC,
	//	GetPos().iX() - GetScale().ihX(),
	//	GetPos().iY() - GetScale().ihY(),
	//	GetPos().iX() + GetScale().ihX(),
	//	GetPos().iY() + GetScale().ihY()
	//);

	// ±×¸®±â
}

void Player::Release()
{
}