#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Effect : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect();
	~Effect();

	// delete Function
	Effect(const Effect& _Other) = delete;
	Effect(Effect&& _Other) noexcept = delete;
	Effect& operator=(const Effect& _Other) = delete;
	Effect& operator=(Effect&& _Other) noexcept = delete;

	class GameEngineRenderer* EffectRender = nullptr;

protected:

private:
	void Start() override;
};

