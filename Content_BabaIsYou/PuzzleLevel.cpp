#include "PuzzleLevel.h"

#include "Background_Gray.h"

PuzzleLevel::PuzzleLevel()
{
}

PuzzleLevel::~PuzzleLevel()
{
}

void PuzzleLevel::Start()
{
	Background_Gray* BackgroundUI = CreateActor<Background_Gray>();
	BackgroundUI->Init("Background_Gray.bmp");
}
void PuzzleLevel::Update(float _Delta)
{

}