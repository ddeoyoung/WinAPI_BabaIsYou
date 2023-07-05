#include "PuzzleLevel3.h"
#include <GameEngineCore/GameEngineRenderer.h>

PuzzleLevel3::PuzzleLevel3()
{
}

PuzzleLevel3::~PuzzleLevel3()
{
}

void PuzzleLevel3::Start()
{

}

void PuzzleLevel3::LevelStart(GameEngineLevel* _PrevLevel)
{
	PuzzleLevelInit("stage3.bmp");
	PuzzleLevelBase::LevelStart(_PrevLevel);
}

void PuzzleLevel3::Update(float _Delta)
{
	PuzzleLevelBase::Update(_Delta);
}

void PuzzleLevel3::LevelEnd(GameEngineLevel* _NextLevel)
{
	PuzzleLevelBase::LevelEnd(_NextLevel);
}
