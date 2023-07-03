#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "TutorialLevel.h"

// Ό³Έν :
class PuzzleLevel2 : public TutorialLevel
{
public:
	// constrcuter destructer
	PuzzleLevel2();
	~PuzzleLevel2();

	// delete Function
	PuzzleLevel2(const PuzzleLevel2& _Other) = delete;
	PuzzleLevel2(PuzzleLevel2&& _Other) noexcept = delete;
	PuzzleLevel2& operator=(const PuzzleLevel2& _Other) = delete;
	PuzzleLevel2& operator=(PuzzleLevel2&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
};

