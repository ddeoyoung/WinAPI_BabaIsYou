#include "PuzzleLevel2.h"
#include <GameEngineCore/GameEngineRenderer.h>

PuzzleLevel2::PuzzleLevel2()
{
}

PuzzleLevel2::~PuzzleLevel2()
{
}

void PuzzleLevel2::Start()
{

}

void PuzzleLevel2::LevelStart(GameEngineLevel* _PrevLevel)
{
	PuzzleLevelInit("stage2.bmp");
	PuzzleLevelBase::LevelStart(_PrevLevel);
}

void PuzzleLevel2::Update(float _Delta)
{
	PuzzleLevelBase::Update(_Delta);
}

void PuzzleLevel2::LevelEnd(GameEngineLevel* _NextLevel)
{
	PuzzleLevelBase::LevelEnd(_NextLevel);
}
