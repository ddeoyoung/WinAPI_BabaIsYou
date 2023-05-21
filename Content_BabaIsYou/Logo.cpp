#include "Logo.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"

Logo::Logo()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	SetPos(WinScale);
}

Logo::~Logo()
{
}

void Logo::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("Logo.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Logo\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Logo.bmp"), 1, 3);

		GameEngineRenderer* LogoRender = CreateRenderer("Logo.bmp", RenderOrder::PlayUI);

		LogoRender->CreateAnimation("UI", "Logo.bmp", 0, 2, 0.2f, true);
		LogoRender->ChangeAnimation("UI");
		LogoRender->SetRenderScaleToTexture();

		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		LogoRender->SetRenderScale(WinScale);
	}
}
