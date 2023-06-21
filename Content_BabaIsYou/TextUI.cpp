#include "TextUI.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentsEnum.h"

TextUI::TextUI()
{
}

TextUI::~TextUI()
{
}

void TextUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Text.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");

		Text = ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Text.bmp"), 38, 2);
	}
}

void TextUI::SetText()
{

}