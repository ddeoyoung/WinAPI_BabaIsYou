#include "Background_Gray.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

Background_Gray::Background_Gray()
{
}

Background_Gray::~Background_Gray()
{
}

void Background_Gray::Start()
{

}

void Background_Gray::Init(const std::string& _FileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");

		GameEngineWindowTexture* Back = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Background_Gray.bmp"));
	}

	BackRender = CreateRenderer("Background_Gray.bmp", RenderOrder::BackGround);

	GameEngineWindowTexture* Back = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Back->GetScale();
	BackRender->SetRenderScale(Scale);
	SetPos({ Scale.hX(), Scale.hY() });
}