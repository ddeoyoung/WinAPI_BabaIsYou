#include "TitleLogo.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

TitleLogo::TitleLogo()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	SetPos(WinScale);

	// float4 Pos = { (WinScale., 600) };
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("TitleLogo.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Title\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("TitleLogo.bmp"), 1, 3);

		GameEngineRenderer* TitleLogoRender = CreateRenderer("TitleLogo.bmp", RenderOrder::PlayUI);

		TitleLogoRender->CreateAnimation("TitleLogoUI", "TitleLogo.bmp", 0, 2, 0.2f, true);
		TitleLogoRender->ChangeAnimation("TitleLogoUI");
		TitleLogoRender->SetRenderScaleToTexture();
	}
}
