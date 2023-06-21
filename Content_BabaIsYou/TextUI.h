#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "ContentsEnum.h"

// ���� :
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

	virtual void SetPuzzleText(char _Text);
	virtual void SetTextScale(const float4& _Scale);

	void SetTextColor(TEXT_COLOR _Color)
	{
		TextColor = _Color;
	}

	void ShakeText();

protected:

private:
	void Start() override;

	class GameEngineRenderer* TextRender = nullptr;
	class GameEngineSprite* Text = nullptr;

	TEXT_COLOR TextColor = TEXT_COLOR::WHITE;

	int SpriteIndex;
	char CurText;
	float4 TextScale;
};

