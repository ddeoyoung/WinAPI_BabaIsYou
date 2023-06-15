#include "WorldMapSelect.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>

WorldMapSelect::WorldMapSelect()
{
}

WorldMapSelect::~WorldMapSelect()
{
}

void WorldMapSelect::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("WorldMapSelect.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WorldMapSelect.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("WorldMapSelect.bmp", 1, 3);
	}


}

void WorldMapSelect::Update(float _Delta)
{

}