#include "Player.h"
#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Baba.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");


		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Baba.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("Baba.Bmp", RenderOrder::Play);
		Ptr->SetRenderScale({ 70, 70 });
		Ptr->SetTexture("Baba.Bmp");
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 0, -50 });
		Ptr->SetRenderScale({ 70, 10 });
		Ptr->SetTexture("HPBar.bmp");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();


	SetPos(WinScale.Half());

}

void Player::Update(float _Delta)
{

	float Speed = 1000.0f;

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->Renderer->SetTexture("Baba.Bmp");
		NewBullet->Renderer->SetRenderScale({ 20, 20 });
		NewBullet->SetDir(float4::RIGHT);
		NewBullet->SetPos(GetPos());
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