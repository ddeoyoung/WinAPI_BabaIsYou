#include "PuzzleLevel.h"
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"
#include "Background_Gray.h"
#include "Background_Black.h"

PuzzleLevel::PuzzleLevel()
{
}

PuzzleLevel::~PuzzleLevel()
{
}

void PuzzleLevel::Start()
{
	Background_Gray* BackgroundUI_Gray = CreateActor<Background_Gray>();
	BackgroundUI_Gray->Init("Background_Gray.bmp");

	Background_Black* BackgroundUI_Black = CreateActor<Background_Black>();
	BackgroundUI_Black->Init("Background_Black.bmp", {850, 600});


	if (false == ResourcesManager::GetInst().IsLoadTexture("Actor.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Actor.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Actor.bmp", 24, 40);
	}


	// BackGridPos : Background_Black Pos와 같이
	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	float4 BackScale = { 850, 600 };
	float4 BackGridPos = { WinScale.X - (BackScale.X / 2), WinScale.Y - (BackScale.Y / 2) };

	// 21 x 15 개의 타일맵을 Background_Black 위치에 생성
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 2);
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			// Index 22, 23은 이미지 없음
			TileGrid->SetTile(x, y, 555, BackGridPos);
		}
	}


	// Player
	//TileGrid->SetTile(5, 2, 2, BackGridPos);

	GameEngineRenderer* TileRenderer = TileGrid->GetTile(5, 2);
	TileRenderer->CreateAnimation("BabaAnimation", "Actor.bmp", 2, 5, 0.1f, true);
	TileRenderer->ChangeAnimation("BabaAnimation");
}

void PuzzleLevel::Update(float _Delta)
{

}