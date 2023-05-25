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
	if (false == ResourcesManager::GetInst().IsLoadTexture("Background_Black.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");
		GameEngineWindowTexture* Back = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Background_Black.bmp"));
		
		GameEngineRenderer* BackRender = CreateRenderer("Background_Black.bmp", RenderOrder::BackGround);

		float4 Scale = Back->GetScale();
		Scale.X *= 2.0f;
		Scale.Y *= 2.0f;

		BackRender->SetRenderScale(Scale);

	}
}



}

