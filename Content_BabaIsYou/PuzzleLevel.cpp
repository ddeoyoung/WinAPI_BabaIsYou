#include "PuzzleLevel.h"
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>


#include "ContentsEnum.h"
#include "Background_Gray.h"
#include "Background_Black.h"
#include "Background_Pixel.h"
#include "FadeAnimation.h"
#include "TextUI.h"

PuzzleLevel::PuzzleLevel()
{
}

PuzzleLevel::~PuzzleLevel()
{
}

void PuzzleLevel::Start()
{
	// Background
	BackgroundUI_Gray = CreateActor<Background_Gray>();
	BackgroundUI_Gray->Init("Background_Gray.bmp");
	BackgroundUI_Black = CreateActor<Background_Black>();
	BackgroundUI_Black->Init("Background_Black.bmp", {850, 600});

	// Fade Animation
	FadeUI = CreateActor<FadeAnimation>();
	FadeUI->FadeIn();

	//// TextUI
	//Text = CreateActor<TextUI>();

	//Text->SetPuzzleText('A');
	//Text->SetTextScale({ 30, 30 });
	//Text->SetPos({50, 50});

	// 퍼즐 타일 SpriteSheet
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

	// 21 x 15 개의 타일맵 생성
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 2);
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			// 22, 23 : 이미지 없음
			TileGrid->SetTile(x, y, 22, BackGridPos);
		}
	}



	// MapTexture - Stage 1
	Background_Pixel* MapDataImage = CreateActor<Background_Pixel>();
	MapDataImage->Init("stage1.bmp", { 850, 600 });
	MapTexture = ResourcesManager::GetInst().FindTexture("stage1.bmp");

	//MapDataImage->Init("WallTest.bmp", { 850, 600 });
	//MapTexture = ResourcesManager::GetInst().FindTexture("WallTest.bmp");

	MapDataImage->Off();

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			float fx = x;
			float fy = y;
			
			TileRenderer = TileGrid->GetTile(x, y);

			// WALL
			if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 0, 0))
			{ 
				TileGrid->SetTile(x, y, 290, BackGridPos);
				TileRenderer->CreateAnimationToFrame("WALL", "Actor.bmp", { 290, 314, 338 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WALL");
			}

			// GRASS
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 180, 0))
			{
				TileGrid->SetTile(x, y, 506, BackGridPos);
				TileRenderer->CreateAnimationToFrame("GRASS", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
				TileRenderer->ChangeAnimation("GRASS");
			}

			// BABA
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 0))
			{
				TileGrid->SetTile(x, y, 10, BackGridPos);
				TileRenderer->CreateAnimationToFrame("BABA", "Actor.bmp", { 2, 26, 50 }, 0.2f, true);
				TileRenderer->ChangeAnimation("BABA");
			}

			// BLOCK
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 100))
			{
				TileGrid->SetTile(x, y, 737, BackGridPos);
				TileRenderer->CreateAnimationToFrame("BLOCK", "Actor.bmp", { 737, 761, 785 }, 0.2f, true);
				TileRenderer->ChangeAnimation("BLOCK");
			}

			// FLAG
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 255, 0))
			{
				TileGrid->SetTile(x, y, 728, BackGridPos);
				TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 728, 752, 776 }, 0.2f, true);
				TileRenderer->ChangeAnimation("FLAG");
			}

			// WALL_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(50, 50, 50))
			{
				TileGrid->SetTile(x, y, 288, BackGridPos);
				TileRenderer->CreateAnimationToFrame("WALL_TEXT", "Actor.bmp", { 288, 312, 336 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WALL_TEXT");
			}

			// IS_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 200))
			{
				TileGrid->SetTile(x, y, 792, BackGridPos);
				TileRenderer->CreateAnimationToFrame("IS_TEXT", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
				TileRenderer->ChangeAnimation("IS_TEXT");
			}

			// FLAG_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 200, 0))
			{
				TileGrid->SetTile(x, y, 726, BackGridPos);
				//TileRenderer->CreateAnimationToFrame("FLAG_TEXT", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("FLAG_TEXT", "Actor.bmp", { 727, 751, 775 }, 0.2f, true);
				TileRenderer->ChangeAnimation("FLAG_TEXT");
			}

			// BABA_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 100, 100))
			{
				TileGrid->SetTile(x, y, 0, BackGridPos);
				TileRenderer->CreateAnimationToFrame("BABA_TEXT", "Actor.bmp", { 0, 24, 48 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("BABA_TEXT", "Actor.bmp", { 1, 25, 49 }, 0.2f, true);
				TileRenderer->ChangeAnimation("BABA_TEXT");
			}

			// YOU_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(100, 50, 50))
			{
				TileGrid->SetTile(x, y, 864, BackGridPos);
				TileRenderer->CreateAnimationToFrame("YOU_TEXT", "Actor.bmp", { 864, 888, 912 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("YOU_TEXT", "Actor.bmp", { 865, 889, 913 }, 0.2f, true);
				TileRenderer->ChangeAnimation("YOU_TEXT");
			}

			// WIN_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 0))
			{
				TileGrid->SetTile(x, y, 864, BackGridPos);
				//TileRenderer->CreateAnimationToFrame("WIN_TEXT", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("WIN_TEXT", "Actor.bmp", { 867, 891, 915 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WIN_TEXT");
			}
			
			// STOP_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 100, 0))
			{
				TileGrid->SetTile(x, y, 868, BackGridPos);
				TileRenderer->CreateAnimationToFrame("STOP_TEXT", "Actor.bmp", { 868, 892, 916 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("STOP_TEXT", "Actor.bmp", { 869, 893, 917 }, 0.2f, true);
				TileRenderer->ChangeAnimation("STOP_TEXT");
			}
		}
	}





}

void PuzzleLevel::Update(float _Delta)
{

}