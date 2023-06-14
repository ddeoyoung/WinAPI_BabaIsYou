#include "WorldMapLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/TileMap.h>

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Background_Gray.h"
#include "Background_WorldMap.h"
#include "FadeAnimation.h"

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
	//FadeUI = CreateActor<FadeAnimation>();

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

	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	float4 BackScale = { 1190 , 650 };
	float4 BackGridPos = { WinScale.X - (BackScale.X / 2) - 10, WinScale.Y - (BackScale.Y / 2) - 5};


	// 31 x 17 개의 타일맵 생성
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("WorldMapNumberBack.bmp", 31, 17, { 38, 38 }, 2);

	NumberGrid = CreateActor<TileMap>();
	NumberGrid->CreateTileMap("Text.bmp", 31, 17, { 38, 38 }, 3);

	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 31; x++)
		{
			//TileGrid->SetTile(x, y, 0, BackGridPos);
			NumberGrid->SetTile(x, y, 0, BackGridPos);
		}
	}

	// 숫자 뒤 배경
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




	// 숫자
	//0
	NumberGrid->SetTile(9, 14, 1, BackGridPos);
	//1
	NumberGrid->SetTile(10, 12, 2, BackGridPos);
	//2
	NumberGrid->SetTile(10, 11, 3, BackGridPos);
	//3
	NumberGrid->SetTile(11, 12, 4, BackGridPos);

}