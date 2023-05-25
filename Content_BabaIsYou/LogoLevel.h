#pragma once
#include <GameEngineCore/GameEngineLevel.h>


// ���� :

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

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	// ���
	class Background_Black* BackgroundUI = nullptr;

	// ���̵� �ִϸ��̼�
	class FadeAnimation* FadeUI = nullptr;

	// �ΰ�
	class Logo* LogoUI = nullptr;
};

