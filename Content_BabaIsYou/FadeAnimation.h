#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

