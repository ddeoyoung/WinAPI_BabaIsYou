#include "PuzzleLevel.h"
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>


#include "Background_Gray.h"

PuzzleLevel::PuzzleLevel()
{
}

PuzzleLevel::~PuzzleLevel()
{
}

void PuzzleLevel::Start()
{
	Background_Gray* BackgroundUI = CreateActor<Background_Gray>();
	BackgroundUI->Init("Background_Gray.bmp");






	if (false == ResourcesManager::GetInst().IsLoadTexture("Actor.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Actor.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet("Actor.bmp", 24, 40);

	}

	//TileObject = CreateActor<TileMap>();

	//TileObject->CreateTileMap("Actor.bmp", 20, 20, { 50, 50 }, 0);
	//for (int y = 0; y < 20; y++)
	//{
	//	for (int x = 0; x < 20; x++)
	//	{
	//		TileObject->SetTile(x, y, 0);
	//	}
	//}
}
void PuzzleLevel::Update(float _Delta)
{

}