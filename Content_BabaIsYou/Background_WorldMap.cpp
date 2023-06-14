#include "Background_WorldMap.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

Background_WorldMap::Background_WorldMap()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	SetPos(WinScale);

}

Background_WorldMap::~Background_WorldMap()
{
}

void Background_WorldMap::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("WorldMap.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WorldMap.bmp"), 1, 3);

		GameEngineRenderer* BackRender = CreateRenderer("WorldMap.bmp", RenderOrder::BackGroundUI);

		BackRender->CreateAnimation("WorldMapBackUI", "WorldMap.bmp", 0, 2, 0.2f, true);
		BackRender->ChangeAnimation("WorldMapBackUI");
		BackRender->SetRenderScaleToTexture();
		//BackRender->SetRenderScale({ 1190 , 650 });
	}
}