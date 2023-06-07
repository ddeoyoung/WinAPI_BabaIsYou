#include "PuzzleActor.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>

#include "ContentsEnum.h"

PuzzleActor::PuzzleActor()
{
}

PuzzleActor::~PuzzleActor()
{
}

void PuzzleActor::Start()
{
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
	float4 BackScale = { 850, 600 };
	float4 BackGridPos = { WinScale.X - (BackScale.X / 2), WinScale.Y - (BackScale.Y / 2) };

	// 21 x 15 타일맵
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, /*RenderOrder::Grid = */ 2);
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			// Index 22, 23은 이미지 없음
			TileGrid->SetTile(x, y, 22, BackGridPos);
		}
	}

	TileRenderer = TileGrid->GetTile(5, 2);
	TileRenderer->CreateAnimationToFrame("Player_Idle", "Actor.bmp", { 2, 26, 50 }, 0.2f, true);
	TileRenderer->ChangeAnimation("Player_Idle");

	TileRenderer->CreateAnimationToFrame("Grass_Idle", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
}

void PuzzleActor::SetPuzzle(const std::string& _AniamtionName, const std::vector<int>& _Index)
{

}