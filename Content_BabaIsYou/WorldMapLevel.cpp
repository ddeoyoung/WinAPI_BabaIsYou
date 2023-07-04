#include "WorldMapLevel.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Background_Gray.h"
#include "Background_WorldMap.h"
#include "FadeAnimation.h"
#include "WorldMapSelect.h"
#include "TextUI.h"

WorldMapLevel::WorldMapLevel()
{

}

WorldMapLevel::~WorldMapLevel()
{
}

void WorldMapLevel::Start()
{
	// WorldMapNumberBack
	if (false == ResourcesManager::GetInst().IsLoadTexture("WorldMapNumberBack.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WorldMapNumberBack.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("WorldMapNumberBack.bmp", 2, 3);
	}

	// WorldMapLine
	if (false == ResourcesManager::GetInst().IsLoadTexture("WorldMapLine.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WorldMapLine.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("WorldMapLine.bmp", 16, 3);
	}

	// PuzzleActor
	if (false == ResourcesManager::GetInst().IsLoadTexture("Actor.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Actor.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Actor.bmp", 24, 40);
	}

	// Text
	if (false == ResourcesManager::GetInst().IsLoadTexture("Text.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Text.bmp"), 38, 2);
	}

	// WorldMapSelect
	if (false == ResourcesManager::GetInst().IsLoadTexture("WorldMapSelect.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\WorldMap\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WorldMapSelect.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("WorldMapSelect.bmp", 1, 3);
	}

}


void WorldMapLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

	// Background
	BackgroundUI = CreateActor<Background_Gray>();
	BackgroundUI->Init("Background_Gray.bmp");
	WorldMapUI = CreateActor<Background_WorldMap>();

	// FadeAnimation
	FadeUI = CreateActor<FadeAnimation>();
	FadeUI->FadeIn();

	// WorldMapSelect
	//SelectUI = CreateActor<WorldMapSelect>();
	//SelectUI->Off();

	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	float4 BackScale = { 1190 , 650 };
	BackGridPos = { WinScale.X - (BackScale.X / 2) - 10, WinScale.Y - (BackScale.Y / 2) - 5 };

	// 31 x 17 개의 타일맵 생성
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("WorldMapNumberBack.bmp", 31, 17, { 38, 38 }, 2);

	NumberGrid = CreateActor<TileMap>();
	NumberGrid->CreateTileMap("Text.bmp", 31, 17, { 38, 38 }, 3);

	SelectGrid = CreateActor<TileMap>();
	SelectGrid->CreateTileMap("Text.bmp", 31, 17, { 38, 38 }, 4);

	SelectGrid->SetLerpSpeed(10.0f);

	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 31; x++)
		{
			// NumberGrid 0번 : 이미지 없음
			//TileGrid->SetTile(x, y, 0, BackGridPos);
			NumberGrid->SetTile(x, y, 0, BackGridPos);
			//SelectGrid->SetTile(x, y, 0, BackGridPos);
		}
	}

	// Stage Number Back
	// 0
	TileGrid->SetTile(9, 14, 0, BackGridPos);
	TileRenderer = TileGrid->GetTile(9, 14);
	TileRenderer->CreateAnimationToFrame("NUMBER_BACK", "WorldMapNumberBack.bmp", { 0, 2, 4 }, 0.2f, true);
	TileRenderer->ChangeAnimation("NUMBER_BACK");

	// 1
	TileGrid->SetTile(10, 12, 0, BackGridPos);
	TileRenderer = TileGrid->GetTile(10, 12);
	//TileRenderer->CreateAnimationToFrame("NUMBER_BACK", "WorldMapNumberBack.bmp", { 0, 2, 4 }, 0.2f, true);
	TileRenderer->ChangeAnimation("NUMBER_BACK");

	// 2
	TileGrid->SetTile(10, 11, 0, BackGridPos);
	TileRenderer = TileGrid->GetTile(10, 11);
	TileRenderer->CreateAnimationToFrame("NUMBER_BACK", "WorldMapNumberBack.bmp", { 0, 2, 4 }, 0.2f, true);
	TileRenderer->ChangeAnimation("NUMBER_BACK");

	// 3
	TileGrid->SetTile(11, 12, 0, BackGridPos);
	TileRenderer = TileGrid->GetTile(11, 12);
	TileRenderer->CreateAnimationToFrame("NUMBER_BACK", "WorldMapNumberBack.bmp", { 0, 2, 4 }, 0.2f, true);
	TileRenderer->ChangeAnimation("NUMBER_BACK");



	// Stage Number
	//0
	NumberGrid->SetTile(9, 14, 1, BackGridPos);
	//1
	NumberGrid->SetTile(10, 12, 2, BackGridPos);
	//2
	NumberGrid->SetTile(10, 11, 3, BackGridPos);
	//3
	NumberGrid->SetTile(11, 12, 4, BackGridPos);




	// BABA IS YOU
	TileRenderer = NumberGrid->GetTile(28, 14);
	TileRenderer->CreateAnimationToFrame("BABA", "Actor.bmp", { 0, 24, 48 }, 0.2f, true);
	TileRenderer->ChangeAnimation("BABA");

	TileRenderer = NumberGrid->GetTile(29, 14);
	TileRenderer->CreateAnimationToFrame("IS", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
	TileRenderer->ChangeAnimation("IS");

	TileRenderer = NumberGrid->GetTile(30, 14);
	TileRenderer->CreateAnimationToFrame("YOU", "Actor.bmp", { 864, 888, 912 }, 0.2f, true);
	TileRenderer->ChangeAnimation("YOU");


	// FLAG IS WIN
	TileRenderer = NumberGrid->GetTile(28, 16);
	TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
	TileRenderer->ChangeAnimation("FLAG");

	TileRenderer = NumberGrid->GetTile(29, 16);
	TileRenderer->CreateAnimationToFrame("IS", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
	TileRenderer->ChangeAnimation("IS");

	TileRenderer = NumberGrid->GetTile(30, 16);
	TileRenderer->CreateAnimationToFrame("WIN", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
	TileRenderer->ChangeAnimation("WIN");



	// WorldMapLine
	TileRenderer = NumberGrid->GetTile(10, 14);
	TileRenderer->CreateAnimationToFrame("LINE_6", "WorldMapLine.bmp", { 6, 22, 38 }, 0.2f, true);
	TileRenderer->ChangeAnimation("LINE_6");

	TileRenderer = NumberGrid->GetTile(10, 13);
	TileRenderer->CreateAnimationToFrame("LINE_10", "WorldMapLine.bmp", { 10, 26, 42 }, 0.2f, true);
	TileRenderer->ChangeAnimation("LINE_10");


	// SelectUI
	SelectGrid->SetTile(SelectX, SelectY, 0, BackGridPos, true);
	TileRenderer = SelectGrid->GetTile(SelectX, SelectY);
	TileRenderer->CreateAnimation("SELECT_UI", "WorldMapSelect.bmp", 0, 2, 0.2f, true);
	TileRenderer->ChangeAnimation("SELECT_UI");



	SelectGrid->SetTile(8, 14, 0, BackGridPos);
	SelectGrid->SetTile(9, 13, 0, BackGridPos);
	SelectGrid->SetTile(9, 15, 0, BackGridPos);
	SelectGrid->SetTile(10, 15, 0, BackGridPos);
	SelectGrid->SetTile(11, 14, 0, BackGridPos);
	SelectGrid->SetTile(11, 13, 0, BackGridPos);
	SelectGrid->SetTile(9, 12, 0, BackGridPos);
	SelectGrid->SetTile(9, 11, 0, BackGridPos);
	SelectGrid->SetTile(10, 10, 0, BackGridPos);
	SelectGrid->SetTile(11, 11, 0, BackGridPos);
	SelectGrid->SetTile(12, 12, 0, BackGridPos);


	// TextUI
	// Stage 0 - BABA IS YOU
	TextUI* TextB = CreateActor<TextUI>();
	TextB->SetPuzzleText('B', StageTextScale);
	TextB->SetPos({ 50, 17 });
	StageTitle0.push_back(TextB);

	TextUI* TextA = CreateActor<TextUI>();
	TextA->SetPuzzleText('A', StageTextScale);
	TextA->SetPos({ 70, 17 });
	StageTitle0.push_back(TextA);

	TextUI* TextB2 = CreateActor<TextUI>();
	TextB2->SetPuzzleText('B', StageTextScale);
	TextB2->SetPos({ 90, 17 });
	StageTitle0.push_back(TextB2);

	TextUI* TextA2 = CreateActor<TextUI>();
	TextA2->SetPuzzleText('A', StageTextScale);
	TextA2->SetPos({ 110, 17 });
	StageTitle0.push_back(TextA2);

	TextUI* TextSpace = CreateActor<TextUI>();
	TextSpace->SetPuzzleText(' ', StageTextScale);
	TextSpace->SetPos({ 130, 17 });
	StageTitle0.push_back(TextSpace);

	TextUI* TextI = CreateActor<TextUI>();
	TextI->SetPuzzleText('I', StageTextScale);
	TextI->SetPos({ 150, 17 });
	StageTitle0.push_back(TextI);

	TextUI* TextS = CreateActor<TextUI>();
	TextS->SetPuzzleText('S', StageTextScale);
	TextS->SetPos({ 170, 17 });
	StageTitle0.push_back(TextS);

	TextUI* TextSpace0 = CreateActor<TextUI>();
	TextSpace0->SetPuzzleText(' ', StageTextScale);
	TextSpace0->SetPos({ 190, 17 });
	StageTitle0.push_back(TextSpace0);

	TextUI* TextY = CreateActor<TextUI>();
	TextY->SetPuzzleText('Y', StageTextScale);
	TextY->SetPos({ 210, 17 });
	StageTitle0.push_back(TextY);

	TextUI* TextO = CreateActor<TextUI>();
	TextO->SetPuzzleText('O', StageTextScale);
	TextO->SetPos({ 230, 17 });
	StageTitle0.push_back(TextO);

	TextUI* TextU = CreateActor<TextUI>();
	TextU->SetPuzzleText('U', StageTextScale);
	TextU->SetPos({ 250, 17 });
	StageTitle0.push_back(TextU);



	// TextUI
	// Stage 1 - WHERE DO I GO?
	TextUI* TextW = CreateActor<TextUI>();
	TextW->SetPuzzleText('W', StageTextScale);
	TextW->SetPos({ 50, 17 });
	StageTitle1.push_back(TextW);

	TextUI* TextH = CreateActor<TextUI>();
	TextH->SetPuzzleText('H', StageTextScale);
	TextH->SetPos({ 70, 17 });
	StageTitle1.push_back(TextH);

	TextUI* TextE = CreateActor<TextUI>();
	TextE->SetPuzzleText('E', StageTextScale);
	TextE->SetPos({ 90, 17 });
	StageTitle1.push_back(TextE);

	TextUI* TextR = CreateActor<TextUI>();
	TextR->SetPuzzleText('R', StageTextScale);
	TextR->SetPos({ 110, 17 });
	StageTitle1.push_back(TextR);

	TextUI* TextE1 = CreateActor<TextUI>();
	TextE1->SetPuzzleText('E', StageTextScale);
	TextE1->SetPos({ 130, 17 });
	StageTitle1.push_back(TextE1);

	TextUI* TextSpace1 = CreateActor<TextUI>();
	TextSpace1->SetPuzzleText(' ', StageTextScale);
	TextSpace1->SetPos({ 150, 17 });
	StageTitle1.push_back(TextSpace1);

	TextUI* TextD = CreateActor<TextUI>();
	TextD->SetPuzzleText('D', StageTextScale);
	TextD->SetPos({ 170, 17 });
	StageTitle1.push_back(TextD);

	TextUI* TextO1 = CreateActor<TextUI>();
	TextO1->SetPuzzleText('O', StageTextScale);
	TextO1->SetPos({ 190, 17 });
	StageTitle1.push_back(TextO1);

	TextUI* TextSpace2 = CreateActor<TextUI>();
	TextSpace2->SetPuzzleText(' ', StageTextScale);
	TextSpace2->SetPos({ 210, 17 });
	StageTitle1.push_back(TextSpace2);

	TextUI* TextI2 = CreateActor<TextUI>();
	TextI2->SetPuzzleText('I', StageTextScale);
	TextI2->SetPos({ 230, 17 });
	StageTitle1.push_back(TextI2);

	TextUI* TextSpace3 = CreateActor<TextUI>();
	TextSpace3->SetPuzzleText(' ', StageTextScale);
	TextSpace3->SetPos({ 250, 17 });
	StageTitle1.push_back(TextSpace3);

	TextUI* TextG = CreateActor<TextUI>();
	TextG->SetPuzzleText('G', StageTextScale);
	TextG->SetPos({ 270, 17 });
	StageTitle1.push_back(TextG);

	TextUI* TextO2 = CreateActor<TextUI>();
	TextO2->SetPuzzleText('O', StageTextScale);
	TextO2->SetPos({ 290, 17 });
	StageTitle1.push_back(TextO2);

	TextUI* TextQues = CreateActor<TextUI>();
	TextQues->SetPuzzleText('?', StageTextScale);
	TextQues->SetPos({ 310, 17 });
	StageTitle1.push_back(TextQues);


	// TextUI
	// Stage 2 - NOW WHAT IS THIS?
	TextUI* TextN = CreateActor<TextUI>();
	TextN->SetPuzzleText('N', StageTextScale);
	TextN->SetPos({ 50, 17 });
	StageTitle2.push_back(TextN);

	TextUI* TextO3 = CreateActor<TextUI>();
	TextO3->SetPuzzleText('O', StageTextScale);
	TextO3->SetPos({ 70, 17 });
	StageTitle2.push_back(TextO3);

	TextUI* TextW1 = CreateActor<TextUI>();
	TextW1->SetPuzzleText('W', StageTextScale);
	TextW1->SetPos({ 90, 17 });
	StageTitle2.push_back(TextW1);

	TextUI* TextSpace4 = CreateActor<TextUI>();
	TextSpace4->SetPuzzleText(' ', StageTextScale);
	TextSpace4->SetPos({ 110, 17 });
	StageTitle2.push_back(TextSpace4);

	TextUI* TextW2 = CreateActor<TextUI>();
	TextW2->SetPuzzleText('W', StageTextScale);
	TextW2->SetPos({ 130, 17 });
	StageTitle2.push_back(TextW2);

	TextUI* TextH1 = CreateActor<TextUI>();
	TextH1->SetPuzzleText('H', StageTextScale);
	TextH1->SetPos({ 150, 17 });
	StageTitle2.push_back(TextH1);

	TextUI* TextA3 = CreateActor<TextUI>();
	TextA3->SetPuzzleText('A', StageTextScale);
	TextA3->SetPos({ 170, 17 });
	StageTitle2.push_back(TextA3);

	TextUI* TextT = CreateActor<TextUI>();
	TextT->SetPuzzleText('T', StageTextScale);
	TextT->SetPos({ 190, 17 });
	StageTitle2.push_back(TextT);

	TextUI* TextSpace5 = CreateActor<TextUI>();
	TextSpace5->SetPuzzleText(' ', StageTextScale);
	TextSpace5->SetPos({ 210, 17 });
	StageTitle2.push_back(TextSpace5);

	TextUI* TextI3 = CreateActor<TextUI>();
	TextI3->SetPuzzleText('I', StageTextScale);
	TextI3->SetPos({ 230, 17 });
	StageTitle2.push_back(TextI3);

	TextUI* TextS2 = CreateActor<TextUI>();
	TextS2->SetPuzzleText('S', StageTextScale);
	TextS2->SetPos({ 250, 17 });
	StageTitle2.push_back(TextS2);

	TextUI* TextSpace6 = CreateActor<TextUI>();
	TextSpace6->SetPuzzleText(' ', StageTextScale);
	TextSpace6->SetPos({ 270, 17 });
	StageTitle2.push_back(TextSpace6);

	TextUI* TextT1 = CreateActor<TextUI>();
	TextT1->SetPuzzleText('T', StageTextScale);
	TextT1->SetPos({ 290, 17 });
	StageTitle2.push_back(TextT1);

	TextUI* TextH2 = CreateActor<TextUI>();
	TextH2->SetPuzzleText('H', StageTextScale);
	TextH2->SetPos({ 310, 17 });
	StageTitle2.push_back(TextH2);

	TextUI* TextI4 = CreateActor<TextUI>();
	TextI4->SetPuzzleText('I', StageTextScale);
	TextI4->SetPos({ 330, 17 });
	StageTitle2.push_back(TextI4);

	TextUI* TextS3 = CreateActor<TextUI>();
	TextS3->SetPuzzleText('S', StageTextScale);
	TextS3->SetPos({ 350, 17 });
	StageTitle2.push_back(TextS3);

	TextUI* TextQues1 = CreateActor<TextUI>();
	TextQues1->SetPuzzleText('?', StageTextScale);
	TextQues1->SetPos({ 370, 17 });
	StageTitle2.push_back(TextQues1);


	// TextUI - Off
	for (size_t i = 0; i < StageTitle0.size(); i++)
	{
		StageTitle0[i]->Off();
	}

	for (size_t i = 0; i < StageTitle1.size(); i++)
	{
		StageTitle1[i]->Off();
	}

	for (size_t i = 0; i < StageTitle2.size(); i++)
	{
		StageTitle2[i]->Off();
	}

	for (size_t i = 0; i < StageTitle3.size(); i++)
	{
		StageTitle3[i]->Off();
	}
}

void WorldMapLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeUI->Off();
	SelectGrid->DeathTile(SelectX, SelectY);
}


void WorldMapLevel::StageTitleUI(int _SelectX, int _SelectY)
{
	// Stage 0 - BABA IS YOU
	if (_SelectX == 9 && _SelectY == 14)
	{
		//Text->SetPuzzleString("BABA IS YOU");
		for (size_t i = 0; i < StageTitle0.size(); i++)
		{
			StageTitle0[i]->On();
		}

		for (size_t i = 0; i < StageTitle1.size(); i++)
		{
			StageTitle1[i]->Off();
		}

		for (size_t i = 0; i < StageTitle2.size(); i++)
		{
			StageTitle2[i]->Off();
		}

		for (size_t i = 0; i < StageTitle3.size(); i++)
		{
			StageTitle3[i]->Off();
		}
	}

	// Stage 1 - WHERE DO I GO?
	else if (_SelectX == 10 && _SelectY == 12)
	{
		for (size_t i = 0; i < StageTitle0.size(); i++)
		{
			StageTitle0[i]->Off();
		}

		for (size_t i = 0; i < StageTitle1.size(); i++)
		{
			StageTitle1[i]->On();
		}

		for (size_t i = 0; i < StageTitle2.size(); i++)
		{
			StageTitle2[i]->Off();
		}

		for (size_t i = 0; i < StageTitle3.size(); i++)
		{
			StageTitle3[i]->Off();
		}
	}

	// Stage 2 - NOW WHAT IS THIS?
	else if (_SelectX == 10 && _SelectY == 11)
	{
		for (size_t i = 0; i < StageTitle0.size(); i++)
		{
			StageTitle0[i]->Off();
		}

		for (size_t i = 0; i < StageTitle1.size(); i++)
		{
			StageTitle1[i]->Off();
		}

		for (size_t i = 0; i < StageTitle2.size(); i++)
		{
			StageTitle2[i]->On();
		}

		for (size_t i = 0; i < StageTitle3.size(); i++)
		{
			StageTitle3[i]->Off();
		}
	}

	// Stage 3 - OUT OF REACH
	else if (_SelectX == 11 && _SelectY == 12)
	{
		for (size_t i = 0; i < StageTitle0.size(); i++)
		{
			StageTitle0[i]->Off();
		}

		for (size_t i = 0; i < StageTitle1.size(); i++)
		{
			StageTitle1[i]->Off();
		}

		for (size_t i = 0; i < StageTitle2.size(); i++)
		{
			StageTitle2[i]->Off();
		}

		for (size_t i = 0; i < StageTitle3.size(); i++)
		{
			StageTitle3[i]->On();
		}
	}

	else
	{
		// Text->Off();
		for (size_t i = 0; i < StageTitle0.size(); i++)
		{
			StageTitle0[i]->Off();
		}

		for (size_t i = 0; i < StageTitle1.size(); i++)
		{
			StageTitle1[i]->Off();
		}
		
		for (size_t i = 0; i < StageTitle2.size(); i++)
		{
			StageTitle2[i]->Off();
		}

		for (size_t i = 0; i < StageTitle3.size(); i++)
		{
			StageTitle3[i]->Off();
		}
	}

}

void WorldMapLevel::MoveCheck()
{
	if (true == GameEngineInput::IsDown('D'))
	{
		NextTile = SelectGrid->GetTile(SelectX + 1, SelectY);

		if (nullptr == NextTile)
		{
			IsMove = SelectGrid->LerpTile(SelectX, SelectY, SelectX + 1, SelectY, BackGridPos);

			if (true == IsMove)
			{
				SelectX += 1;
			}
		}
	}

	else if (true == GameEngineInput::IsDown('W'))
	{
		NextTile = SelectGrid->GetTile(SelectX, SelectY - 1);

		if (nullptr == NextTile)
		{
			IsMove = SelectGrid->LerpTile(SelectX, SelectY, SelectX, SelectY - 1, BackGridPos);

			if (true == IsMove)
			{
				SelectY -= 1;
			}
		}
	}

	else if (true == GameEngineInput::IsDown('A'))
	{
		NextTile = SelectGrid->GetTile(SelectX - 1, SelectY);

		if (nullptr == NextTile)
		{
			IsMove = SelectGrid->LerpTile(SelectX, SelectY, SelectX - 1, SelectY, BackGridPos);

			if (true == IsMove)
			{
				SelectX -= 1;
			}
		}
	}

	else if (true == GameEngineInput::IsDown('S'))
	{
		NextTile = SelectGrid->GetTile(SelectX, SelectY + 1);

		if (nullptr == NextTile)
		{
			IsMove = SelectGrid->LerpTile(SelectX, SelectY, SelectX, SelectY + 1, BackGridPos);

			if (true == IsMove)
			{
				SelectY += 1;
			}
		}
	}

	StageTitleUI(SelectX, SelectY);
}


void WorldMapLevel::Update(float _Delta)
{
	MoveCheck();

	// 스테이지 이동
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (SelectX == 9 && SelectY == 14)
		{
			FadeUI->On();
			FadeUI->FadeOut();
			StageName = "TutorialLevel";
		}

		if (SelectX == 10 && SelectY == 12)
		{
			FadeUI->On();
			FadeUI->FadeOut();
			StageName = "PuzzleLevel1";
		}

		if (SelectX == 10 && SelectY == 11)
		{
			FadeUI->On();
			FadeUI->FadeOut();
			StageName = "PuzzleLevel2";
		}

		if (SelectX == 11 && SelectY == 12)
		{
			FadeUI->On();
			FadeUI->FadeOut();
			StageName = "PuzzleLevel3";
		}

	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeIn")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		FadeUI->Off();
	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeOut")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		GameEngineCore::ChangeLevel(StageName);
	}
}