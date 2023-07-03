#include "TutorialLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

#include "ContentsEnum.h"
#include "Background_Gray.h"
#include "Background_Black.h"
#include "Background_Pixel.h"
#include "CongratsUI.h"
#include "FadeAnimation.h"
#include "TextUI.h"
#include "Effect.h"
#include "MoveUI.h"

#include <sstream>

TutorialLevel::TutorialLevel()
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	PuzzleLevelInit("Tutorial.bmp");
}
void TutorialLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}
void TutorialLevel::Start()
{
}
void TutorialLevel::Update(float _Delta)
{

}