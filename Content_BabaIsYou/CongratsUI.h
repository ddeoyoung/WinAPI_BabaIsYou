#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class CongratsUI : public GameEngineActor
{
public:
	// constrcuter destructer
	CongratsUI();
	~CongratsUI();

	// delete Function
	CongratsUI(const CongratsUI& _Other) = delete;
	CongratsUI(CongratsUI&& _Other) noexcept = delete;
	CongratsUI& operator=(const CongratsUI& _Other) = delete;
	CongratsUI& operator=(CongratsUI&& _Other) noexcept = delete;

	GameEngineRenderer* CongratsRender = nullptr;

	void SetCongratsAnimation();

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	float4 WinScale = {};

};

