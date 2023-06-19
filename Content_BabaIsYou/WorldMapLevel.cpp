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

WorldMapLevel::WorldMapLevel()
{

}

WorldMapLevel::~WorldMapLevel()
{
}

void WorldMapLevel::Start()
{

	BackgroundUI = CreateActor<Background_Gray>();
	BackgroundUI->Init("Background_Gray.bmp");

	WorldMapUI = CreateActor<Background_WorldMap>();
	FadeUI = CreateActor<FadeAnimation>();
	FadeUI->FadeIn();

	// Text
	if (false == ResourcesManager::GetInst().IsLoadTexture("Text.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Text.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Text.bmp", 38, 2);
	}

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

	// WorldMapSelect
	if (false == ResourcesManager::GetInst().IsLoadTexture("WorldMapSelect.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WorldMapSelect.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("WorldMapSelect.bmp", 1, 3);
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

	// 스테이지 숫자 뒤 배경
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



	// 스테이지 숫자
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
	TileRenderer->CreateAnimationToFrame("BABA_TEXT", "Actor.bmp", { 0, 24, 48 }, 0.2f, true);
	TileRenderer->ChangeAnimation("BABA_TEXT");

	TileRenderer = NumberGrid->GetTile(29, 14);
	TileRenderer->CreateAnimationToFrame("IS_TEXT", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
	TileRenderer->ChangeAnimation("IS_TEXT");

	TileRenderer = NumberGrid->GetTile(30, 14);
	TileRenderer->CreateAnimationToFrame("YOU_TEXT", "Actor.bmp", { 864, 888, 912 }, 0.2f, true);
	TileRenderer->ChangeAnimation("YOU_TEXT");


	// FLAG IS WIN
	TileRenderer = NumberGrid->GetTile(28, 16);
	TileRenderer->CreateAnimationToFrame("FLAG_TEXT", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
	TileRenderer->ChangeAnimation("FLAG_TEXT");

	TileRenderer = NumberGrid->GetTile(29, 16);
	TileRenderer->CreateAnimationToFrame("IS_TEXT", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
	TileRenderer->ChangeAnimation("IS_TEXT");

	TileRenderer = NumberGrid->GetTile(30, 16);
	TileRenderer->CreateAnimationToFrame("WIN_TEXT", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
	TileRenderer->ChangeAnimation("WIN_TEXT");



	// WorldMapLine
	TileRenderer = NumberGrid->GetTile(10, 14);
	TileRenderer->CreateAnimationToFrame("LINE_6", "WorldMapLine.bmp", { 6, 22, 38 }, 0.2f, true);
	TileRenderer->ChangeAnimation("LINE_6");

	TileRenderer = NumberGrid->GetTile(10, 13);
	TileRenderer->CreateAnimationToFrame("LINE_10", "WorldMapLine.bmp", { 10, 26, 42 }, 0.2f, true);
	TileRenderer->ChangeAnimation("LINE_10");


	//// WorldMapSelect
	//SelectGrid->SetTile(10, 14, 0, BackGridPos, true);
	//SelectGrid->SetTile(10, 13, 0, BackGridPos, true);
	//SelectGrid->SetTile(10, 12, 0, BackGridPos, true);
	//SelectGrid->SetTile(10, 11, 0, BackGridPos, true);
	//SelectGrid->SetTile(11, 12, 0, BackGridPos, true);


	SelectGrid->SetTile(9, 14, 0, BackGridPos, true);
	Select_X = 9;
	Select_Y = 14;

	//SelectGrid->SetTile(Select_X, Select_Y, 0, BackGridPos, true);
	TileRenderer = SelectGrid->GetTile(Select_X, Select_Y);
	TileRenderer->CreateAnimation("SELECT_UI", "WorldMapSelect.bmp", 0, 2, 0.2f, true);
	TileRenderer->ChangeAnimation("SELECT_UI");
}

void WorldMapLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('D'))
	{
		if (true == SelectGrid->MoveTile(Select_X, Select_Y, Select_X + 1, Select_Y, BackGridPos))
		{
			Select_X += 1;
		}
	}

	else if (true == GameEngineInput::IsDown('W'))
	{
		SelectGrid->MoveTile(Select_X, Select_Y, Select_X, Select_Y - 1, BackGridPos);
		Select_Y -= 1;
	}

	else if (true == GameEngineInput::IsDown('A'))
	{
		SelectGrid->MoveTile(Select_X, Select_Y, Select_X - 1, Select_Y, BackGridPos);
		Select_X -= 1;
	}

	else if (true == GameEngineInput::IsDown('S'))
	{
		SelectGrid->MoveTile(Select_X, Select_Y, Select_X, Select_Y + 1, BackGridPos);
		Select_Y += 1;
	}



	// 스테이지 이동
	else if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (Select_X == 10 && Select_Y == 12)
		{
			FadeUI->FadeOut();
			StageName = "PuzzleLevel";
		}
	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeOut")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		GameEngineCore::ChangeLevel(StageName);
	}
}