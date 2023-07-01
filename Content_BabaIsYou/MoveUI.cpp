#include "MoveUI.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include "ContentsEnum.h"

MoveUI::MoveUI()
{
}

MoveUI::~MoveUI()
{
}

void MoveUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("MoveTutorialUI.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Puzzle\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MoveTutorialUI.bmp"));
	}
	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();

	Renderer = CreateRenderer("MoveTutorialUI.bmp", RENDER_ORDER::PLAY_UI);
	//Renderer->SetRenderScaleToTexture();
	Renderer->SetRenderScale({ 120, 120});
	SetPos({ WinScale.X, 200 });
}