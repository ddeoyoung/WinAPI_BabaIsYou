#include "Button.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"


Button::Button()
{
}

Button::~Button()
{
}

void Button::Start()
{

}

void Button::SetButton(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Title\\");
		Texture = ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(FileName), 1, 2);
	}

	ButtonRender = CreateRenderer(FileName, RENDER_ORDER::PLAY_UI);

	Scale = { 400, 60 };

	ButtonRender->SetSprite(FileName, 0);

	//ButtonRender->CreateAnimation("Button", _FileName, 0, 1, 0.2f, true);
	//ButtonRender->ChangeAnimation("Button");
	ButtonRender->SetRenderScale(Scale);

}
