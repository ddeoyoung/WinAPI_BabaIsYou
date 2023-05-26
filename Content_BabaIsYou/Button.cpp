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
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Title\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(_FileName), 1, 2);

		GameEngineWindowTexture* StartButton = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}

	ButtonRender = CreateRenderer(_FileName, RenderOrder::PlayUI);

	ButtonRender->CreateAnimation("Button", _FileName, 0, 1, 0.2f, true);
	ButtonRender->ChangeAnimation("Button");
	ButtonRender->SetRenderScale({400, 60});
}