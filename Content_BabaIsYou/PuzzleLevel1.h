#pragma once
#include "PuzzleLevelBase.h"

// Ό³Έν :
class PuzzleLevel1 : public PuzzleLevelBase
{
public:
	// constrcuter destructer
	PuzzleLevel1();
	~PuzzleLevel1();

	// delete Function
	PuzzleLevel1(const PuzzleLevel1& _Other) = delete;
	PuzzleLevel1(PuzzleLevel1&& _Other) noexcept = delete;
	PuzzleLevel1& operator=(const PuzzleLevel1& _Other) = delete;
	PuzzleLevel1& operator=(PuzzleLevel1&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	void Start() override;
	void Update(float _Delta) override;
};

