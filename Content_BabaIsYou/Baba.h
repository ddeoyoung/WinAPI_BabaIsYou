#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "ContentsEnum.h"

// Ό³Έν :
class Baba : public GameEngineActor
{
public:
	// constrcuter destructer
	Baba();
	~Baba();

	// delete Function
	Baba(const Baba& _Other) = delete;
	Baba(Baba&& _Other) noexcept = delete;
	Baba& operator=(const Baba& _Other) = delete;
	Baba& operator=(Baba&& _Other) noexcept = delete;

	void CheckDir();
	void ChangeAnimationState(BABA_DIR _Dir);


protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* BabaRenderer = nullptr;

	std::string AnimationName = "";

	BABA_DIR Dir = BABA_DIR::LEFT;

};

