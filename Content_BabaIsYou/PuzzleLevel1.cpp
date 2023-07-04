#include "PuzzleLevel1.h"

PuzzleLevel1::PuzzleLevel1()
{
}

PuzzleLevel1::~PuzzleLevel1()
{
}

void PuzzleLevel1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PuzzleLevelInit("stage1.bmp");
}
void PuzzleLevel1::LevelEnd(GameEngineLevel* _NextLevel)
{
	PuzzleLevelBase::LevelEnd(_NextLevel);
}

void PuzzleLevel1::Start()
{
}
void PuzzleLevel1::Update(float _Delta)
{
	PuzzleLevelBase::Update(_Delta);
}