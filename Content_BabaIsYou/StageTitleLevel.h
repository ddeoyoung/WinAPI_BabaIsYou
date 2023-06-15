#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class StageTitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	StageTitleLevel();
	~StageTitleLevel();

	// delete Function
	StageTitleLevel(const StageTitleLevel& _Other) = delete;
	StageTitleLevel(StageTitleLevel&& _Other) noexcept = delete;
	StageTitleLevel& operator=(const StageTitleLevel& _Other) = delete;
	StageTitleLevel& operator=(StageTitleLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;


};

