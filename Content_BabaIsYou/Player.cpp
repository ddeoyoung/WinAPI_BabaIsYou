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
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");


		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		FolderPath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));


		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Baba.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		// MainRenderer->SetRenderScale({ 200, 200 });

		MainRenderer->CreateAnimation("Idle", "Left_Player.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Run", "Left_Player.bmp", 3, 6, 0.1f, true);
		MainRenderer->ChangeAnimation("Idle");
		MainRenderer->SetRenderScaleToTexture();

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

	if (MovePos.X != 0.0f || MovePos.Y != 0.0f)
	{
		MainRenderer->ChangeAnimation("Run");
	}
	else
	{
		MainRenderer->ChangeAnimation("Idle");
	}

	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		float4 Pos = GameEngineWindow::MainWindow.GetMousePos();


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