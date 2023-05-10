#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

// Contents
#include "Player.h"
#include "BackGround.h"


PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->Init("StageTest.Bmp");

	CreateActor<Player>();
}


void PlayLevel::Update(float _Delta)
{
	// GameEngineCore::ChangeLevel("TitleLevel");
}

void PlayLevel::Render()
{

}

void PlayLevel::Release()
{

}