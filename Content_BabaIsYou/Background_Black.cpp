#include "Background_Black.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
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

void Background_Black::Init(const std::string& _FileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");

		GameEngineWindowTexture* Back = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Background_Black.bmp"));
	}

	BackRender = CreateRenderer("Background_Black.bmp", RenderOrder::Grid);

	GameEngineWindowTexture* Back = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Back->GetScale();
	BackRender->SetRenderScale(Scale);
	SetPos({ Scale.hX(), Scale.hY() });
}

