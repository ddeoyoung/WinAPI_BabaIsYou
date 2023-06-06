#include "PuzzleLevel.h"
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

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

	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();

	// 34 x 24 개의 타일맵을 Background_Black 에 생성
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 2);
	for (int y = 0; y < 24; y++)
	{
		for (int x = 0; x < 34; x++)
		{
			// TilePos : Background_Black Pos와 같이
			TileGrid->SetTile(x, y, 3, { WinScale.X - 425, WinScale.Y - 300 });
		}
	}
}

void PuzzleLevel::Update(float _Delta)
{

}