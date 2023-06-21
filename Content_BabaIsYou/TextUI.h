#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "ContentsEnum.h"

// Ό³Έν :
class TextUI : public GameEngineActor
{
public:
	// constrcuter destructer
	TextUI();
	~TextUI();

	// delete Function
	TextUI(const TextUI& _Other) = delete;
	TextUI(TextUI&& _Other) noexcept = delete;
	TextUI& operator=(const TextUI& _Other) = delete;
	TextUI& operator=(TextUI&& _Other) noexcept = delete;

	void SetText(char _Text);

	void SetTextColor(TEXT_COLOR _Color)
	{
		TextColor = _Color;
	}

	void SetTextScale();

	void ShakeText();

protected:

private:
	void Start() override;

	class GameEngineRenderer* TextRender = nullptr;
	class GameEngineSprite* Text = nullptr;

	TEXT_COLOR TextColor = TEXT_COLOR::WHITE;
	char CurText;
};

