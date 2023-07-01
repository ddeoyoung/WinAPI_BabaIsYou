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

	void SetEffect();

	void SetDir(float4 _Dir)
	{
		Dir = _Dir;
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	float4 Dir;

	float Speed = 0.0f;
};

