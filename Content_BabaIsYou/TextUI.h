#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

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

	virtual void SetPuzzleText(char _Text, const float4& _Scale);

	void SetPuzzleString(std::string _TextString);

	void SetTextColor(TEXT_COLOR _Color)
	{
		TextColor = _Color;
	}

	void MoveText();

protected:

private:
	void Start() override;

	class GameEngineRenderer* TextRender = nullptr;
	class GameEngineSprite* Text = nullptr;

	TEXT_COLOR TextColor = TEXT_COLOR::WHITE;

	int SpriteIndex = 0;
	char CurText = 'a';
	float4 TextScale;
};

