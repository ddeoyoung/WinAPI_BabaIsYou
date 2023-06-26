#include "PuzzleLevel.h"
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "ContentsEnum.h"
#include "Background_Gray.h"
#include "Background_Black.h"
#include "Background_Pixel.h"
#include "FadeAnimation.h"
#include "TextUI.h"
#include "Baba.h"

PuzzleLevel::PuzzleLevel()
{
}

PuzzleLevel::~PuzzleLevel()
{
}

void PuzzleLevel::Start()
{
	// Background
	BackgroundUI_Gray = CreateActor<Background_Gray>();
	BackgroundUI_Gray->Init("Background_Gray.bmp");
	BackgroundUI_Black = CreateActor<Background_Black>();
	BackgroundUI_Black->Init("Background_Black.bmp", {850, 600});

	// Fade Animation
	FadeUI = CreateActor<FadeAnimation>();
	FadeUI->FadeIn();

	// Puzzle Tiles
	if (false == ResourcesManager::GetInst().IsLoadTexture("Actor.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Default\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Actor.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Actor.bmp", 24, 40);
	}

	WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	BackGridPos = { WinScale.X - (BackScale.X / 2), WinScale.Y - (BackScale.Y / 2) };


	// 21 x 15 개의 타일맵 생성
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 2);


	// 맵 세팅
	// MapTexture - Stage 1
	Background_Pixel* MapDataImage = CreateActor<Background_Pixel>();
	MapDataImage->Init("stage1.bmp", { 850, 600 });
	MapTexture = ResourcesManager::GetInst().FindTexture("stage1.bmp");
	MapDataImage->Off();

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			float fx = x;
			float fy = y;

			// WALL
			if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 0, 0))
			{ 
				TileRenderer = TileGrid->SetTile(x, y, 290, BackGridPos);
				TileRenderer->CreateAnimationToFrame("WALL", "Actor.bmp", { 290, 314, 338 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WALL");
			}

			// GRASS
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 180, 0))
			{
				TileRenderer = TileGrid->SetTile(x, y, 506, BackGridPos);
				TileRenderer->CreateAnimationToFrame("GRASS", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
				TileRenderer->ChangeAnimation("GRASS");
			}

			// BABA
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 0))
			{
				TileRenderer = TileGrid->SetTile(x, y, 2, BackGridPos);
				TileRenderer->CreateAnimationToFrame("Baba_Left", "Actor.bmp", { 10, 34, 58 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Right", "Actor.bmp", { 2, 26, 50 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Up", "Actor.bmp", { 6, 30, 54 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Down", "Actor.bmp", { 14, 38, 62 }, 0.2f, true);

				TileRenderer->CreateAnimationToFrame("Baba_Left2", "Actor.bmp", { 11, 35, 59 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Right2", "Actor.bmp", { 3, 27, 51 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Up2", "Actor.bmp", { 7, 31, 55 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Down2", "Actor.bmp", { 15, 39, 63 }, 0.2f, true);

				TileRenderer->CreateAnimationToFrame("Baba_Left3", "Actor.bmp", { 12, 36, 60 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Right3", "Actor.bmp", { 4, 28, 52 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Up3", "Actor.bmp", { 8, 32, 56 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Down3", "Actor.bmp", { 16, 40, 64 }, 0.2f, true);

				TileRenderer->CreateAnimationToFrame("Baba_Left4", "Actor.bmp", { 13, 37, 61 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Right4", "Actor.bmp", { 5, 29, 53 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Up4", "Actor.bmp", { 9, 33, 57 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("Baba_Down4", "Actor.bmp", { 17, 41, 65 }, 0.2f, true);
				TileRenderer->ChangeAnimation("Baba_Down");

				MainRenderer = TileRenderer;
			}

			// BLOCK
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 100))
			{
				TileRenderer = TileGrid->SetTile(x, y, 737, BackGridPos);
				TileRenderer->CreateAnimationToFrame("BLOCK", "Actor.bmp", { 737, 761, 785 }, 0.2f, true);
				TileRenderer->ChangeAnimation("BLOCK");
			}

			// FLAG
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 255, 0))
			{
				TileRenderer = TileGrid->SetTile(x, y, 728, BackGridPos);
				TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 728, 752, 776 }, 0.2f, true);
				TileRenderer->ChangeAnimation("FLAG");
			}

			// WALL_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(50, 50, 50))
			{
				TileRenderer = TileGrid->SetTile(x, y, 288, BackGridPos);
				TileRenderer->CreateAnimationToFrame("WALL_TEXT", "Actor.bmp", { 288, 312, 336 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WALL_TEXT");
			}

			// IS_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 200))
			{
				TileRenderer = TileGrid->SetTile(x, y, 792, BackGridPos);
				TileRenderer->CreateAnimationToFrame("IS_TEXT", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
				TileRenderer->ChangeAnimation("IS_TEXT");
			}

			// FLAG_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 200, 0))
			{
				TileRenderer = TileGrid->SetTile(x, y, 726, BackGridPos);
				//TileRenderer->CreateAnimationToFrame("FLAG_TEXT", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("FLAG_TEXT", "Actor.bmp", { 727, 751, 775 }, 0.2f, true);
				TileRenderer->ChangeAnimation("FLAG_TEXT");
			}

			// BABA_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 100, 100))
			{
				TileRenderer = TileGrid->SetTile(x, y, 0, BackGridPos);
				TileRenderer->CreateAnimationToFrame("BABA_TEXT", "Actor.bmp", { 0, 24, 48 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("BABA_TEXT", "Actor.bmp", { 1, 25, 49 }, 0.2f, true);
				TileRenderer->ChangeAnimation("BABA_TEXT");
			}

			// YOU_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(100, 50, 50))
			{
				TileRenderer = TileGrid->SetTile(x, y, 864, BackGridPos);
				TileRenderer->CreateAnimationToFrame("YOU_TEXT", "Actor.bmp", { 864, 888, 912 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("YOU_TEXT", "Actor.bmp", { 865, 889, 913 }, 0.2f, true);
				TileRenderer->ChangeAnimation("YOU_TEXT");
			}

			// WIN_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 0))
			{
				TileRenderer = TileGrid->SetTile(x, y, 864, BackGridPos);
				//TileRenderer->CreateAnimationToFrame("WIN_TEXT", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("WIN_TEXT", "Actor.bmp", { 867, 891, 915 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WIN_TEXT");
			}
			
			// STOP_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 100, 0))
			{
				TileRenderer = TileGrid->SetTile(x, y, 868, BackGridPos);
				TileRenderer->CreateAnimationToFrame("STOP_TEXT", "Actor.bmp", { 868, 892, 916 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("STOP_TEXT", "Actor.bmp", { 869, 893, 917 }, 0.2f, true);
				TileRenderer->ChangeAnimation("STOP_TEXT");
			}
		}
	}

	// 퍼즐 정의
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			float fx = x;
			float fy = y;

			// WALL
			if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 0, 0))
			{
				TileRenderer->SetName("WALL");
				ACTOR_TYPE Wall_Type = ACTOR_TYPE::ACTOR;
				ACTOR_BEHAVE Wall_Behave = ACTOR_BEHAVE::STOP;
			}

			// GRASS
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 180, 0))
			{
				TileRenderer->SetName("GRASS");
				ACTOR_TYPE Grass_Type = ACTOR_TYPE::ACTOR;
				ACTOR_BEHAVE Grass_Behave = ACTOR_BEHAVE::NONE;
			}

			// BABA
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 0))
			{
				TileRenderer->SetName("BABA");
				ACTOR_TYPE Baba_Type = ACTOR_TYPE::ACTOR;
				ACTOR_BEHAVE Baba_Behave = ACTOR_BEHAVE::YOU;
			}

			// BLOCK
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 100))
			{
				TileRenderer->SetName("BLOCK");
				ACTOR_TYPE Block_Type = ACTOR_TYPE::ACTOR;
				ACTOR_BEHAVE Block_Behave = ACTOR_BEHAVE::NONE;
			}

			// FLAG
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 255, 0))
			{
				TileRenderer->SetName("FLAG");
				ACTOR_TYPE Flag_Type = ACTOR_TYPE::ACTOR;
				ACTOR_BEHAVE Flag_Behave = ACTOR_BEHAVE::WIN;
			}

			// WALL_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(50, 50, 50))
			{
				TileRenderer->SetName("WALL_TEXT");
				ACTOR_TYPE WallText_Type = ACTOR_TYPE::SUBJECT_TEXT;
				ACTOR_BEHAVE WallText_Behave = ACTOR_BEHAVE::PUSH;
			}

			// IS_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 200))
			{
				TileRenderer->SetName("IS_TEXT");
				ACTOR_TYPE IsText_Type = ACTOR_TYPE::VERB_TEXT;
				ACTOR_BEHAVE IsText_Behave = ACTOR_BEHAVE::PUSH;
			}

			// FLAG_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 200, 0))
			{
				TileRenderer->SetName("FLAG_TEXT");
				ACTOR_TYPE FlagText_Type = ACTOR_TYPE::SUBJECT_TEXT;
				ACTOR_BEHAVE FlagText_Behave = ACTOR_BEHAVE::PUSH;
			}

			// BABA_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 100, 100))
			{
				TileRenderer->SetName("BABA_TEXT");
				ACTOR_TYPE BabaText_Type = ACTOR_TYPE::SUBJECT_TEXT;
				ACTOR_BEHAVE BabaText_Behave = ACTOR_BEHAVE::PUSH;
			}

			// YOU_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(100, 50, 50))
			{
				TileRenderer->SetName("YOU_TEXT");
				ACTOR_TYPE YouText_Type = ACTOR_TYPE::BEHAVE_TEXT;
				ACTOR_BEHAVE YouText_Behave = ACTOR_BEHAVE::PUSH;
			}

			// WIN_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 0))
			{
				TileRenderer->SetName("WIN_TEXT");
				ACTOR_TYPE WinText_Type = ACTOR_TYPE::BEHAVE_TEXT;
				ACTOR_BEHAVE WinText_Behave = ACTOR_BEHAVE::PUSH;
			}

			// STOP_TEXT
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 100, 0))
			{
				TileRenderer->SetName("STOP_TEXT");
				ACTOR_TYPE StopText_Type = ACTOR_TYPE::BEHAVE_TEXT;
				ACTOR_BEHAVE StopText_Behave = ACTOR_BEHAVE::PUSH;
			}
		}
	}

	TileGrid->SetLerpSpeed(10.0f);

	// Rule Check
	// 
	// 문장 완성은 왼쪽->오른쪽, 위쪽->아래쪽 으로만 가능
	// Is (VERB_TEXT) 기준으로 상하좌우 체크 -> 문장이 만들어진다면
	// ACTOR_TYPE이 SUBJECT_TEXT인 타일은,  BEHAVE_TEXT의 ACTOR_BEHAVE 속성을 갖는다
	
	// (주어) (동사) (행동)
}



void PuzzleLevel::Update(float _Delta)
{
	// RIGHT
	if (true == GameEngineInput::IsDown('D'))
	{
		// 오른쪽 타일
		NextTile = TileGrid->GetTile(Index_X + 1, Index_Y);

		if (nullptr != NextTile)
		{
			int Count = 0;

			// 다음 타일이 없을 때까지 체크
			while (nullptr != NextTile)
			{
				Count++;
				NextTile = TileGrid->GetTile(Index_X + Count, Index_Y);
			}

			// 여러 타일 한 번에 밀기
			for (int i = Count; i >= 0; i--)
			{
				IsMove = TileGrid->LerpTile(Index_X + i, Index_Y, Index_X + i + 1, Index_Y, BackGridPos);
			}

			if (true == IsMove)
			{
				Index_X += 1;
			}
		}

		else if (nullptr == NextTile)
		{
			IsMove = TileGrid->LerpTile(Index_X, Index_Y, Index_X + 1, Index_Y, BackGridPos);

			if (true == IsMove)
			{
				Index_X += 1;

				// 바바 애니메이션 변경
				switch (BabaMoveStep)
				{
				case 0:
					MainRenderer->ChangeAnimation("Baba_Right");
					BabaMoveStep += 1;
					break;
				case 1:
					MainRenderer->ChangeAnimation("Baba_Right2");
					BabaMoveStep += 1;
					break;
				case 2:
					MainRenderer->ChangeAnimation("Baba_Right3");
					BabaMoveStep += 1;
					break;
				case 3:
					MainRenderer->ChangeAnimation("Baba_Right4");
					BabaMoveStep = 0;
					break;
				default:
					break;
				}
			}
		}
	}

	// UP
	else if (true == GameEngineInput::IsDown('W'))
	{
		NextTile = TileGrid->GetTile(Index_X, Index_Y - 1);

		if (nullptr != NextTile)
		{
			int Count = 0;

			while (nullptr != NextTile)
			{
				Count++;
				NextTile = TileGrid->GetTile(Index_X, Index_Y - Count);
			}

			for (int i = Count; i >= 0; i--)
			{
				IsMove = TileGrid->LerpTile(Index_X, Index_Y - i, Index_X, Index_Y - i - 1, BackGridPos);
			}

			if (true == IsMove)
			{
				Index_Y -= 1;
			}
		}

		else if (nullptr == NextTile)
		{
			IsMove = TileGrid->LerpTile(Index_X, Index_Y, Index_X, Index_Y - 1, BackGridPos);

			if (true == IsMove)
			{
				Index_Y -= 1;

				switch (BabaMoveStep)
				{
				case 0:
					MainRenderer->ChangeAnimation("Baba_Up");
					BabaMoveStep += 1;
					break;
				case 1:
					MainRenderer->ChangeAnimation("Baba_Up2");
					BabaMoveStep += 1;
					break;
				case 2:
					MainRenderer->ChangeAnimation("Baba_Up3");
					BabaMoveStep += 1;
					break;
				case 3:
					MainRenderer->ChangeAnimation("Baba_Up4");
					BabaMoveStep = 0;
					break;
				default:
					break;
				}
			}
		}
	}

	// LEFT
	else if (true == GameEngineInput::IsDown('A'))
	{
		// 왼쪽 타일
		NextTile = TileGrid->GetTile(Index_X - 1, Index_Y);

		if (nullptr != NextTile)
		{
			int Count = 0;

			while (nullptr != NextTile)
			{
				Count++;
				NextTile = TileGrid->GetTile(Index_X - Count, Index_Y);
			}

			for (int i = Count; i >= 0; i--)
			{
				IsMove = TileGrid->LerpTile(Index_X - i, Index_Y, Index_X - i - 1, Index_Y, BackGridPos);
			}

			if (true == IsMove)
			{
				Index_X -= 1;
			}
		}

		else if (nullptr == NextTile)
		{
			IsMove = TileGrid->LerpTile(Index_X, Index_Y, Index_X - 1, Index_Y, BackGridPos);

			if (true == IsMove)
			{
				Index_X -= 1;

				switch (BabaMoveStep)
				{
				case 0:
					MainRenderer->ChangeAnimation("Baba_Left");
					BabaMoveStep += 1;
					break;
				case 1:
					MainRenderer->ChangeAnimation("Baba_Left2");
					BabaMoveStep += 1;
					break;
				case 2:
					MainRenderer->ChangeAnimation("Baba_Left3");
					BabaMoveStep += 1;
					break;
				case 3:
					MainRenderer->ChangeAnimation("Baba_Left4");
					BabaMoveStep = 0;
					break;
				default:
					break;
				}
			}
		}
	}

	// DOWN
	else if (true == GameEngineInput::IsDown('S'))
	{
		// 아래쪽 타일
		NextTile = TileGrid->GetTile(Index_X, Index_Y + 1);

		if (nullptr != NextTile)
		{
			int Count = 0;

			while (nullptr != NextTile)
			{
				Count++;
				NextTile = TileGrid->GetTile(Index_X, Index_Y + Count);
			}

			for (int i = Count; i >= 0; i--)
			{
				IsMove = TileGrid->LerpTile(Index_X, Index_Y + i, Index_X, Index_Y + i + 1, BackGridPos);
			}

			if (true == IsMove)
			{
				Index_Y += 1;
			}
		}

		else if (nullptr == NextTile)
		{
			IsMove = TileGrid->LerpTile(Index_X, Index_Y, Index_X, Index_Y + 1, BackGridPos);

			if (true == IsMove)
			{
				Index_Y += 1;

				switch (BabaMoveStep)
				{
				case 0:
					MainRenderer->ChangeAnimation("Baba_Down");
					BabaMoveStep += 1;
					break;
				case 1:
					MainRenderer->ChangeAnimation("Baba_Down2");
					BabaMoveStep += 1;
					break;
				case 2:
					MainRenderer->ChangeAnimation("Baba_Down3");
					BabaMoveStep += 1;
					break;
				case 3:
					MainRenderer->ChangeAnimation("Baba_Down4");
					BabaMoveStep = 0;
					break;
				default:
					break;
				}
			}
		}
	}
}