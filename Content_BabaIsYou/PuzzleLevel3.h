#pragma once
#include "PuzzleLevelBase.h"

// Ό³Έν :
class PuzzleLevel3 : public PuzzleLevelBase
{
public:
	// constrcuter destructer
	PuzzleLevel3();
	~PuzzleLevel3();

	// delete Function
	PuzzleLevel3(const PuzzleLevel3& _Other) = delete;
	PuzzleLevel3(PuzzleLevel3&& _Other) noexcept = delete;
	PuzzleLevel3& operator=(const PuzzleLevel3& _Other) = delete;
	PuzzleLevel3& operator=(PuzzleLevel3&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
};

