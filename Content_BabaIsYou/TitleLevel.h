#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class TitleLogo;
class Background_Black;
class FadeAnimation;
class Button;
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;


protected:


private:
	void Start() override;
	void Update(float _Delta) override;

	TitleLogo* TitleLogoUI = nullptr;

	Background_Black* BackgroundUI = nullptr;

	FadeAnimation* FadeUI = nullptr;

	Button* StartButton = nullptr;
};

