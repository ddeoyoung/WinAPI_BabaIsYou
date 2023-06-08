#include "PuzzleLevel.h"
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>


#include "ContentsEnum.h"
#include "Background_Gray.h"
#include "Background_Black.h"
#include "Background_Pixel.h"

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

	// Puzzle Tile 설정
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
	float4 BackScale = { 840, 600 };
	float4 BackGridPos = { WinScale.X - (BackScale.X / 2), WinScale.Y - (BackScale.Y / 2) };

	// 21 x 15 개의 타일맵
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 2);
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			// 22, 23은 이미지 없음
			// 785는 블럭이미지
			TileGrid->SetTile(x, y, 22, BackGridPos);
		}
	}

	// GRASS
	TileGrid->SetTile(6, 1, 506, BackGridPos);
	TileGrid->SetTile(19, 2, 506, BackGridPos);
	TileGrid->SetTile(15, 3, 506, BackGridPos);
	TileGrid->SetTile(16, 4, 506, BackGridPos);
	TileGrid->SetTile(18, 7, 506, BackGridPos);

	TileGrid->SetTile(19, 10, 506, BackGridPos);
	TileGrid->SetTile(19, 11, 506, BackGridPos);
	TileGrid->SetTile(18, 11, 506, BackGridPos);

	TileGrid->SetTile(16, 13, 506, BackGridPos);

	TileGrid->SetTile(1, 7, 506, BackGridPos);
	TileGrid->SetTile(2, 8, 506, BackGridPos);

	// WALL
	TileGrid->SetTile(8, 2, 290, BackGridPos);
	TileGrid->SetTile(9, 2, 290, BackGridPos);
	TileGrid->SetTile(10, 2, 290, BackGridPos);
	TileGrid->SetTile(11, 2, 290, BackGridPos);
	TileGrid->SetTile(12, 2, 290, BackGridPos);
	TileGrid->SetTile(13, 2, 290, BackGridPos);
	TileGrid->SetTile(14, 2, 290, BackGridPos);

	TileGrid->SetTile(8, 3, 290, BackGridPos);
	TileGrid->SetTile(8, 4, 290, BackGridPos);
	TileGrid->SetTile(8, 5, 290, BackGridPos);

	TileGrid->SetTile(7, 5, 290, BackGridPos);
	TileGrid->SetTile(6, 5, 290, BackGridPos);
	TileGrid->SetTile(5, 5, 290, BackGridPos);
	TileGrid->SetTile(4, 5, 290, BackGridPos);

	TileGrid->SetTile(4, 6, 290, BackGridPos);
	TileGrid->SetTile(4, 7, 290, BackGridPos);
	TileGrid->SetTile(4, 8, 290, BackGridPos);
	TileGrid->SetTile(4, 9, 290, BackGridPos);

	TileGrid->SetTile(5, 9, 290, BackGridPos);
	TileGrid->SetTile(6, 9, 290, BackGridPos);
	TileGrid->SetTile(7, 9, 290, BackGridPos);
	TileGrid->SetTile(8, 9, 290, BackGridPos);
	TileGrid->SetTile(9, 9, 290, BackGridPos);
	TileGrid->SetTile(10, 9, 290, BackGridPos);
	TileGrid->SetTile(11, 9, 290, BackGridPos);
	TileGrid->SetTile(12, 9, 290, BackGridPos);
	TileGrid->SetTile(13, 9, 290, BackGridPos);
	TileGrid->SetTile(14, 9, 290, BackGridPos);

	TileGrid->SetTile(14, 3, 290, BackGridPos);
	TileGrid->SetTile(14, 4, 290, BackGridPos);
	TileGrid->SetTile(14, 5, 290, BackGridPos);
	TileGrid->SetTile(14, 6, 290, BackGridPos);
	TileGrid->SetTile(14, 7, 290, BackGridPos);
	TileGrid->SetTile(14, 8, 290, BackGridPos);

	TileGrid->SetTile(8, 10, 290, BackGridPos);
	TileGrid->SetTile(8, 11, 290, BackGridPos);
	TileGrid->SetTile(8, 12, 290, BackGridPos);
	TileGrid->SetTile(8, 13, 290, BackGridPos);

	TileGrid->SetTile(9, 13, 290, BackGridPos);
	TileGrid->SetTile(10, 13, 290, BackGridPos);
	TileGrid->SetTile(11, 13, 290, BackGridPos);
	TileGrid->SetTile(12, 13, 290, BackGridPos);
	TileGrid->SetTile(13, 13, 290, BackGridPos);

	TileGrid->SetTile(14, 13, 290, BackGridPos);
	TileGrid->SetTile(14, 12, 290, BackGridPos);
	TileGrid->SetTile(14, 11, 290, BackGridPos);
	TileGrid->SetTile(14, 10, 290, BackGridPos);
	TileGrid->SetTile(14, 9, 290, BackGridPos);


	// BABA IS YOU
	TileGrid->SetTile(5, 11, 0, BackGridPos);
	TileGrid->SetTile(5, 12, 792, BackGridPos);
	TileGrid->SetTile(5, 13, 864, BackGridPos);

	// BABA
	TileGrid->SetTile(12, 11, 10, BackGridPos);

	// WALL IS STOP
	TileGrid->SetTile(10, 10, 288, BackGridPos);
	TileGrid->SetTile(10, 11, 792, BackGridPos);
	TileGrid->SetTile(10, 12, 868, BackGridPos);

	// FLAG
	TileGrid->SetTile(6, 7, 726, BackGridPos);
	TileGrid->SetTile(10, 7, 728, BackGridPos);

	// IS
	TileGrid->SetTile(10, 4, 792, BackGridPos);

	// WIN
	TileGrid->SetTile(12, 5, 866, BackGridPos);


	GameEngineRenderer* TileRenderer = TileGrid->GetTile(12, 5);
	TileRenderer->CreateAnimationToFrame("WIN_Text", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
	TileRenderer->ChangeAnimation("WIN_Text");

	TileRenderer = TileGrid->GetTile(10, 7);
	TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 728, 752, 776 }, 0.2f, true);
	TileRenderer->ChangeAnimation("FLAG");

	TileRenderer = TileGrid->GetTile(6, 7);
	TileRenderer->CreateAnimationToFrame("FLAG_Text", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
	TileRenderer->ChangeAnimation("FLAG_Text");

	TileRenderer = TileGrid->GetTile(12, 11);
	TileRenderer->CreateAnimationToFrame("BABA", "Actor.bmp", { 2, 26, 50 }, 0.2f, true);
	TileRenderer->ChangeAnimation("BABA");


	TileRenderer = TileGrid->GetTile(6, 1);
	TileRenderer->CreateAnimationToFrame("GRASS", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
	TileRenderer->ChangeAnimation("GRASS");

	TileRenderer = TileGrid->GetTile(19, 2);
	TileRenderer->CreateAnimationToFrame("GRASS", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
	TileRenderer->ChangeAnimation("GRASS");

	TileRenderer = TileGrid->GetTile(15, 3);
	TileRenderer->CreateAnimationToFrame("GRASS", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
	TileRenderer->ChangeAnimation("GRASS");

	TileRenderer = TileGrid->GetTile(16, 4);
	TileRenderer->CreateAnimationToFrame("GRASS", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
	TileRenderer->ChangeAnimation("GRASS");

	TileRenderer = TileGrid->GetTile(18, 7);
	TileRenderer->CreateAnimationToFrame("GRASS", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
	TileRenderer->ChangeAnimation("GRASS");



	Background_Pixel* BackgroundUI_Pixel = CreateActor<Background_Pixel>();
	BackgroundUI_Pixel->Init("stage1.bmp", { 850, 600 });

	BackgroundUI_Pixel->GetColor
	

}

void PuzzleLevel::Update(float _Delta)
{

}