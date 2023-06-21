#include "TextUI.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineString.h>

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

	TextRender = CreateRenderer("Text.bmp", RENDER_ORDER::BACKGROUND_UI);
	TextRender->UICameraSetting();

	//TextRender->SetRenderPos({ 50, 50 });
}

void TextUI::SetPuzzleText(char _Text, const float4& _Scale)
{
	CurText = _Text;
	//CurText = toupper(_Text);

	int ColorIndex = static_cast<int>(TextColor) * 38;

	if ('0' <= CurText && '9' >= CurText)
	{
		// SpriteIndex 0 = None
		// SpriteIndex 1 ~ 10 = 0 ~ 9
		// ¼ýÀÚ = ColorIndex + 1
		SpriteIndex = ColorIndex + CurText - '0' + 1;
		TextRender->SetSprite("Text.bmp", SpriteIndex);
	}
	else if ('A' <= CurText && 'Z' >= CurText)
	{
		SpriteIndex = ColorIndex + 11 + CurText - 'A';
		TextRender->SetSprite("Text.bmp", SpriteIndex);
	}
	else if ('?' == CurText)
	{
		SpriteIndex = ColorIndex + 37;
		TextRender->SetSprite("Text.bmp", SpriteIndex);
	}
	else
	{
		SpriteIndex = ColorIndex + 0;
		TextRender->SetSprite("Text.bmp", SpriteIndex);
	}

	TextScale = _Scale;
	TextRender->SetRenderScale(TextScale);
}

void TextUI::SetPuzzleString(std::string _TextString) 
{

}


void TextUI::MoveText()
{

}