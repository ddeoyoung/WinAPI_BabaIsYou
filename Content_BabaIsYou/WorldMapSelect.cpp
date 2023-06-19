#include "WorldMapSelect.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/TileMap.h>

#include "ContentsEnum.h"

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

	SelectRender = CreateRenderer("WorldMapSelect.bmp", RenderOrder::PlayUI);
	SelectRender->CreateAnimation("SELECT", "WorldMapSelect.bmp", 0, 2, 0.2f, true);
	SelectRender->ChangeAnimation("SELECT");
}

void WorldMapSelect::Init()
{
	
}

void WorldMapSelect::Update(float _Delta)
{

}