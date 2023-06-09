#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>


// 설명 :
class LogoLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	LogoLevel();
	~LogoLevel();

	// delete Function
	LogoLevel(const LogoLevel& _Other) = delete;
	LogoLevel(LogoLevel&& _Other) noexcept = delete;
	LogoLevel& operator=(const LogoLevel& _Other) = delete;
	LogoLevel& operator=(LogoLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer BGMPlayer;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	void Start() override;
	void Update(float _Delta) override;

	// 배경
	class Background_Black* BackgroundUI = nullptr;

	// 페이드 애니메이션
	class FadeAnimation* FadeUI = nullptr;

	// 로고
	class Logo* LogoUI = nullptr;

};

