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

	// ≈∏¿œ∏ 
	//GameEnginePath FilePath;
	//FilePath.SetCurrentPath();
	//FilePath.MoveParentToExistsChild("ContentsResources");
	//FilePath.MoveChild("ContentsResources\\WorldMap\\");
	//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WorldMapSelect.bmp"));
	//ResourcesManager::GetInst().CreateSpriteSheet("WorldMapSelect.bmp", 1, 3);

	//TileObject = CreateActor<TileMap>();
	//TileObject->CreateTileMap("WorldMapSelect.bmp", 50, 50, { 32, 32 }, 3);
	//for (int y = 0; y < 50; y++)
	//{
	//	for (int x = 0; x < 50; x++)
	//	{
	//		TileObject->SetTile(x, y, 0);
	//	}
	//}
}