#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class FadeAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeAnimation();
	~FadeAnimation();

	// delete Function
	FadeAnimation(const FadeAnimation& _Other) = delete;
	FadeAnimation(FadeAnimation&& _Other) noexcept = delete;
	FadeAnimation& operator=(const FadeAnimation& _Other) = delete;
	FadeAnimation& operator=(FadeAnimation&& _Other) noexcept = delete;

	bool CheckAnimationEnd();
	bool IsAnimationEnd = false;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* FadeRender = nullptr;
};

