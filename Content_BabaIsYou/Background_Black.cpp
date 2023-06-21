#include "Background_Black.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>
#include "ContentsEnum.h"

Background_Black::Background_Black()
{
}

Background_Black::~Background_Black()
{
}

void Background_Black::Start()
{

}

void Background_Black::Init(const std::string& _FileName, float4 _Scale)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");

		GameEngineWindowTexture* Back = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Background_Black.bmp"));
	}

	GameEngineWindowTexture* Back = ResourcesManager::GetInst().FindTexture(_FileName);
	BackRender = CreateRenderer("Background_Black.bmp", RENDER_ORDER::GRID);
	BackRender->SetRenderScale(_Scale);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	SetPos(WinScale);

}

