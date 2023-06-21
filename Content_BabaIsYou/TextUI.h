#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	void SetText();

	void SetTextScale();

	void ShakeText();

protected:

private:
	void Start() override;
	class GameEngineRenderer* TextRender = nullptr;
	class GameEngineSprite* Text = nullptr;
};

