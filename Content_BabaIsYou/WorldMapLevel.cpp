#include "WorldMapLevel.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Background_Gray.h"
#include "Background_WorldMap.h"
#include "FadeAnimation.h"
#include "WorldMapSelect.h"
#include "TextUI.h"

WorldMapLevel::WorldMapLevel()
{

}

WorldMapLevel::~WorldMapLevel()
{
}

void WorldMapLevel::Start()
{
	// Background
	BackgroundUI = CreateActor<Background_Gray>();
	BackgroundUI->Init("Background_Gray.bmp");
	WorldMapUI = CreateActor<Background_WorldMap>();

	// FadeAnimation
	FadeUI = CreateActor<FadeAnimation>();
	FadeUI->FadeIn();

	// WorldMapSelect
	SelectUI = CreateActor<WorldMapSelect>();
	SelectUI->Off();

	// TextUI
	Text = CreateActor<TextUI>();
	Text->SetPos({ 50, 20 });
	Text->Off();

	// WorldMapNumberBack
	if (false == ResourcesManager::GetInst().IsLoadTexture("WorldMapNumberBack.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WorldMapNumberBack.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("WorldMapNumberBack.bmp", 2, 3);
	}

	// WorldMapLine
	if (false == ResourcesManager::GetInst().IsLoadTexture("WorldMapLine.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WorldMapLine.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("WorldMapLine.bmp", 16, 3);
	}

	// PuzzleActor
	if (false == ResourcesManager::GetInst().IsLoadTexture("Actor.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Actor.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Actor.bmp", 24, 40);
	}



	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	float4 BackScale = { 1190 , 650 };
	BackGridPos = { WinScale.X - (BackScale.X / 2) - 10, WinScale.Y - (BackScale.Y / 2) - 5};


	// 31 x 17 개의 타일맵 생성
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("WorldMapNumberBack.bmp", 31, 17, { 38, 38 }, 2);

	NumberGrid = CreateActor<TileMap>();
	NumberGrid->CreateTileMap("Text.bmp", 31, 17, { 38, 38 }, 3);

	SelectGrid = CreateActor<TileMap>();
	SelectGrid->CreateTileMap("Text.bmp", 31, 17, { 38, 38 }, 4);

	SelectGrid->SetLerpSpeed(10.0f);

	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 31; x++)
		{
			// NumberGrid 0번 : 이미지 없음
			//TileGrid->SetTile(x, y, 0, BackGridPos);
			NumberGrid->SetTile(x, y, 0, BackGridPos);
			//SelectGrid->SetTile(x, y, 0, BackGridPos);
		}
	}

	// Stage Number Back
	// 0
	TileGrid->SetTile(9, 14, 0, BackGridPos);
	TileRenderer = TileGrid->GetTile(9, 14);
	TileRenderer->CreateAnimationToFrame("NUMBER_BACK", "WorldMapNumberBack.bmp", {0, 2, 4}, 0.2f, true);
	TileRenderer->ChangeAnimation("NUMBER_BACK");

	// 1
	TileGrid->SetTile(10, 12, 0, BackGridPos);
	TileRenderer = TileGrid->GetTile(10, 12);
	TileRenderer->CreateAnimationToFrame("NUMBER_BACK", "WorldMapNumberBack.bmp", { 0, 2, 4 }, 0.2f, true);
	TileRenderer->ChangeAnimation("NUMBER_BACK");

	// 2
	TileGrid->SetTile(10, 11, 0, BackGridPos);
	TileRenderer = TileGrid->GetTile(10, 11);
	TileRenderer->CreateAnimationToFrame("NUMBER_BACK", "WorldMapNumberBack.bmp", { 0, 2, 4 }, 0.2f, true);
	TileRenderer->ChangeAnimation("NUMBER_BACK");

	// 3
	TileGrid->SetTile(11, 12, 0, BackGridPos);
	TileRenderer = TileGrid->GetTile(11, 12);
	TileRenderer->CreateAnimationToFrame("NUMBER_BACK", "WorldMapNumberBack.bmp", { 0, 2, 4 }, 0.2f, true);
	TileRenderer->ChangeAnimation("NUMBER_BACK");



	// Stage Number
	//0
	NumberGrid->SetTile(9, 14, 1, BackGridPos);
	//1
	NumberGrid->SetTile(10, 12, 2, BackGridPos);
	//2
	NumberGrid->SetTile(10, 11, 3, BackGridPos);
	//3
	NumberGrid->SetTile(11, 12, 4, BackGridPos);




	// BABA IS YOU
	TileRenderer = NumberGrid->GetTile(28, 14);
	TileRenderer->CreateAnimationToFrame("BABA", "Actor.bmp", { 0, 24, 48 }, 0.2f, true);
	TileRenderer->ChangeAnimation("BABA");

	TileRenderer = NumberGrid->GetTile(29, 14);
	TileRenderer->CreateAnimationToFrame("IS", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
	TileRenderer->ChangeAnimation("IS");

	TileRenderer = NumberGrid->GetTile(30, 14);
	TileRenderer->CreateAnimationToFrame("YOU", "Actor.bmp", { 864, 888, 912 }, 0.2f, true);
	TileRenderer->ChangeAnimation("YOU");


	// FLAG IS WIN
	TileRenderer = NumberGrid->GetTile(28, 16);
	TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
	TileRenderer->ChangeAnimation("FLAG");

	TileRenderer = NumberGrid->GetTile(29, 16);
	TileRenderer->CreateAnimationToFrame("IS", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
	TileRenderer->ChangeAnimation("IS");

	TileRenderer = NumberGrid->GetTile(30, 16);
	TileRenderer->CreateAnimationToFrame("WIN", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
	TileRenderer->ChangeAnimation("WIN");



	// WorldMapLine
	TileRenderer = NumberGrid->GetTile(10, 14);
	TileRenderer->CreateAnimationToFrame("LINE_6", "WorldMapLine.bmp", { 6, 22, 38 }, 0.2f, true);
	TileRenderer->ChangeAnimation("LINE_6");

	TileRenderer = NumberGrid->GetTile(10, 13);
	TileRenderer->CreateAnimationToFrame("LINE_10", "WorldMapLine.bmp", { 10, 26, 42 }, 0.2f, true);
	TileRenderer->ChangeAnimation("LINE_10");


	SelectGrid->SetTile(SelectX, SelectY, 0, BackGridPos, true);
	TileRenderer = SelectGrid->GetTile(SelectX, SelectY);
	TileRenderer->CreateAnimation("SELECT_UI", "WorldMapSelect.bmp", 0, 2, 0.2f, true);
	TileRenderer->ChangeAnimation("SELECT_UI");


	
	SelectGrid->SetTile(8, 14, 0, BackGridPos);
	SelectGrid->SetTile(9, 13, 0, BackGridPos);
	SelectGrid->SetTile(9, 15, 0, BackGridPos);
	SelectGrid->SetTile(10, 15, 0, BackGridPos);
	SelectGrid->SetTile(11, 14, 0, BackGridPos);
	SelectGrid->SetTile(11, 13, 0, BackGridPos);
	SelectGrid->SetTile(9, 12, 0, BackGridPos);
	SelectGrid->SetTile(9, 11, 0, BackGridPos);
	SelectGrid->SetTile(10, 10, 0, BackGridPos);
	SelectGrid->SetTile(11, 11, 0, BackGridPos);
	SelectGrid->SetTile(12, 12, 0, BackGridPos);
}


void WorldMapLevel::StageTitleUI(int _SelectX, int _SelectY)
{
	// Stage 0

	if (_SelectX == 9 && _SelectY == 14)
	{
		Text->On();
		Text->SetPuzzleText('0', { 30, 30});
		//Text->SetPuzzleString("BABA IS YOU");
	}

	// Stage 1
	else if (_SelectX == 10 && _SelectY == 12)
	{
		Text->On();
		Text->SetPuzzleText('1', { 30, 30 });
		//Text->SetPuzzleString("WHERE DO I GO?");
	}

	// Stage 2
	else if (_SelectX == 10 && _SelectY == 11)
	{
		Text->On();
		Text->SetPuzzleText('2', { 30, 30 });
		//Text->SetPuzzleString("NOW WHAT IS THIS?");
	}

	// Stage 3
	else if (_SelectX == 11 && _SelectY == 12)
	{
		Text->On();
		Text->SetPuzzleText('3', { 30, 30 });
		//Text->SetPuzzleString("OUT OF REACH");
	}

	else
	{
		Text->Off();
	}

}

void WorldMapLevel::MoveCheck()
{
	if (true == GameEngineInput::IsDown('D'))
	{
		NextTile = SelectGrid->GetTile(SelectX + 1, SelectY);

		if (nullptr == NextTile)
		{
			IsMove = SelectGrid->LerpTile(SelectX, SelectY, SelectX + 1, SelectY, BackGridPos);

			if (true == IsMove)
			{
				SelectX += 1;
			}
		}
	}

	else if (true == GameEngineInput::IsDown('W'))
	{
		NextTile = SelectGrid->GetTile(SelectX, SelectY - 1);

		if (nullptr == NextTile)
		{
			IsMove = SelectGrid->LerpTile(SelectX, SelectY, SelectX, SelectY - 1, BackGridPos);

			if (true == IsMove)
			{
				SelectY -= 1;
			}
		}
	}

	else if (true == GameEngineInput::IsDown('A'))
	{
		NextTile = SelectGrid->GetTile(SelectX - 1, SelectY);

		if (nullptr == NextTile)
		{
			IsMove = SelectGrid->LerpTile(SelectX, SelectY, SelectX - 1, SelectY, BackGridPos);

			if (true == IsMove)
			{
				SelectX -= 1;
			}
		}
	}

	else if (true == GameEngineInput::IsDown('S'))
	{
		NextTile = SelectGrid->GetTile(SelectX, SelectY + 1);

		if (nullptr == NextTile)
		{
			IsMove = SelectGrid->LerpTile(SelectX, SelectY, SelectX, SelectY + 1, BackGridPos);

			if (true == IsMove)
			{
				SelectY += 1;
			}
		}
	}

	StageTitleUI(SelectX, SelectY);
}


void WorldMapLevel::Update(float _Delta)
{
	MoveCheck();

	// 스테이지 이동
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (SelectX == 10 && SelectY == 12)
		{
			FadeUI->On();
			FadeUI->FadeOut();
			StageName = "PuzzleLevel";
		}
	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeIn")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		FadeUI->Off();
	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeOut")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		GameEngineCore::ChangeLevel(StageName);
	}
}