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

#include <sstream>

PuzzleLevel::PuzzleLevel()
{
	SubjectSet.insert("BABA");
	SubjectSet.insert("WALL");
	SubjectSet.insert("FLAG");

	VerbSet.insert("IS");

	BehaveSet.insert("YOU");
	BehaveSet.insert("STOP");
	BehaveSet.insert("WIN");
}

PuzzleLevel::~PuzzleLevel()
{
}

RuleInfo PuzzleLevel::GetRuleInfo(const std::string& _Text)
{
	RuleInfo Return;

	// ���ڿ� �ڸ���
	std::istringstream StringSplit(_Text);
	std::vector<std::string> ReturnTileNames;
	std::string ReturnTileName;

	while (getline(StringSplit, ReturnTileName, ' ')) //���� ������ ����
	{
		ReturnTileNames.push_back(ReturnTileName);
	}

	Return.Subject = ReturnTileNames[0];
	Return.Verb = ReturnTileNames[1];
	Return.Behave = ReturnTileNames[2];

	return Return;
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


	// 21 x 15 ���� Ÿ�ϸ� ����
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 2);
	TileGrid->SetLerpSpeed(10.0f);

	UpTileGrid = CreateActor<TileMap>();
	UpTileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 10);
	UpTileGrid->SetLerpSpeed(10.0f);


	// �� ����
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

			// WALL_ACTOR
			if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 0, 0))
			{ 
				TileRenderer = TileGrid->SetTile(x, y, 290, BackGridPos);
				TileRenderer->SetName("WALL_ACTOR");
				TileRenderer->CreateAnimationToFrame("WALL_ACTOR", "Actor.bmp", { 290, 314, 338 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WALL_ACTOR");
			}

			// GRASS_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 180, 0))
			{
				TileRenderer = TileGrid->SetTile(x, y, 506, BackGridPos);
				TileRenderer->SetName("GRASS_ACTOR");
				TileRenderer->CreateAnimationToFrame("GRASS_ACTOR", "Actor.bmp", { 506, 530, 554 }, 0.2f, true);
				TileRenderer->ChangeAnimation("GRASS_ACTOR");
			}

			// BABA_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 2, BackGridPos);
				TileRenderer->SetName("BABA_ACTOR");
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
				TileRenderer->ChangeAnimation("Baba_Left");

				MainRenderer = TileRenderer;
			}

			// BLOCK_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 100))
			{
				TileRenderer = TileGrid->SetTile(x, y, 737, BackGridPos);
				TileRenderer->SetName("BLOCK_ACTOR");
				TileRenderer->CreateAnimationToFrame("BLOCK_ACTOR", "Actor.bmp", { 737, 761, 785 }, 0.2f, true);
				TileRenderer->ChangeAnimation("BLOCK_ACTOR");
			}

			// FLAG_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 255, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 728, BackGridPos);
				TileRenderer->SetName("FLAG_ACTOR");
				TileRenderer->CreateAnimationToFrame("FLAG_ACTOR", "Actor.bmp", { 728, 752, 776 }, 0.2f, true);
				TileRenderer->ChangeAnimation("FLAG_ACTOR");
			}

			// WALL
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(50, 50, 50))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 288, BackGridPos);
				TileRenderer->SetName("WALL");
				TileRenderer->CreateAnimationToFrame("WALL", "Actor.bmp", { 288, 312, 336 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WALL");
			}

			// IS
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 200))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 792, BackGridPos);
				TileRenderer->SetName("IS");
				TileRenderer->CreateAnimationToFrame("IS", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
				TileRenderer->ChangeAnimation("IS");
			}

			// FLAG
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 200, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 726, BackGridPos);
				TileRenderer->SetName("FLAG");
				//TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 727, 751, 775 }, 0.2f, true);
				TileRenderer->ChangeAnimation("FLAG");
			}

			// BABA
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 100, 100))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 0, BackGridPos);
				TileRenderer->SetName("BABA");
				TileRenderer->CreateAnimationToFrame("BABA", "Actor.bmp", { 0, 24, 48 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("BABA", "Actor.bmp", { 1, 25, 49 }, 0.2f, true);
				TileRenderer->ChangeAnimation("BABA");
			}

			// YOU
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(100, 50, 50))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 864, BackGridPos);
				TileRenderer->SetName("YOU");
				TileRenderer->CreateAnimationToFrame("YOU", "Actor.bmp", { 864, 888, 912 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("YOU", "Actor.bmp", { 865, 889, 913 }, 0.2f, true);
				TileRenderer->ChangeAnimation("YOU");
			}

			// WIN
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 864, BackGridPos);
				TileRenderer->SetName("WIN");
				//TileRenderer->CreateAnimationToFrame("WIN", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("WIN", "Actor.bmp", { 867, 891, 915 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WIN");
			}
			
			// STOP
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 100, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 868, BackGridPos);
				TileRenderer->SetName("STOP");
				TileRenderer->CreateAnimationToFrame("STOP", "Actor.bmp", { 868, 892, 916 }, 0.2f, true);
				//TileRenderer->CreateAnimationToFrame("STOP", "Actor.bmp", { 869, 893, 917 }, 0.2f, true);
				TileRenderer->ChangeAnimation("STOP");
			}
		}
	}

}

// < Stage 1 ���� ���� >
// �־� : BABA, WALL, FLAG
// ���� : IS
// �ൿ : STOP, WIN, YOU

void PuzzleLevel::UpdateStringRuleCheck()
{
	RuleSet.clear();
	// ������ �����Ǵ��� üũ
	// ���� �ϼ��� ����->������, ����->�Ʒ��ʸ� ����
	// �־� + IS + �ൿ
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			SubjectTileName = "";
			VerbTileName = "";
			BehaveTileName = "";

			CurTile = UpTileGrid->GetTile(x, y);

			if (nullptr != CurTile)
			{
				TileName = CurTile->GetName();

				// �־� �ؽ�Ʈ
				if (SubjectSet.contains(TileName))
				{
					SubjectTileName = TileName + " ";

					CurTile = UpTileGrid->GetTile(x, y + 1);

					if (nullptr != CurTile)
					{
						TileName = CurTile->GetName();

						if (VerbSet.contains(TileName))
						{
							VerbTileName = TileName + " ";
						}

						// �ൿ �ؽ�Ʈ
						CurTile = UpTileGrid->GetTile(x, y + 2);

						if (nullptr != CurTile)
						{
							TileName = CurTile->GetName();

							if (BehaveSet.contains(TileName))
							{
								BehaveTileName = TileName;
								RuleSet.insert(SubjectTileName + VerbTileName + BehaveTileName);
							}
						}
					}
				}
			}


		}
	}
}

std::vector<GameEngineRenderer*> PuzzleLevel::GetBreakTile(const std::string& _PlayerTileName)
{
	GameEngineRenderer* Tile = nullptr;
	std::string TileName = "";

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			Tile = UpTileGrid->GetTile(x, y);

			if (nullptr != Tile)
			{
				TileName = Tile->GetName();

				if (TileName == _PlayerTileName)
				{
					BreakTiles.push_back(Tile);
				}
			}
		}
	}


	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			Tile = TileGrid->GetTile(x, y);

			if (nullptr != Tile)
			{
				TileName = Tile->GetName();

				if (TileName == _PlayerTileName)
				{
					BreakTiles.push_back(Tile);
				}
			}
		}
	}



	return BreakTiles;
}

// Player�ν� ������ �� �ִ� Ÿ�� ����
std::vector<GameEngineRenderer*> PuzzleLevel::GetPlayerTile(TileMap* _TileMap, const std::string& _PlayerTileName)
{
	GameEngineRenderer* Tile = nullptr;
	std::string TileName = "";

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			Tile = _TileMap->GetTile(x, y);

			if (nullptr != Tile)
			{
				TileName = Tile->GetName();

				if (TileName == _PlayerTileName)
				{
					PlayerTiles.push_back(Tile);
				}
			}
		}
	}

	return PlayerTiles;
}

void PuzzleLevel::Update(float _Delta)
{
	// ���� üũ
	UpdateStringRuleCheck();

	MoveCheck();
}

void PuzzleLevel::WinCheck()
{
	
}

void PuzzleLevel::MoveCheck()
{
	RuleInfo Rules;

	for (std::string Text : RuleSet)
	{
		Rules = GetRuleInfo(Text);

		// YOU ������ ���� ��� IsPlayerExist = false
		if (Rules.Behave == "YOU")
		{
			break;
		}
	}

	if (Rules.Behave != "YOU")
	{
		return;
	}

	PlayerTiles.clear();

	TileMap* CurTileMap = nullptr;

	// Player�ν� ������ �� �ִ� Ÿ�� �̸�
	PlayerTileName = Rules.Subject;
	// PlayerTileName = "WALL";
	CurTileMap = TileGrid;
	PlayerTiles = GetPlayerTile(TileGrid, PlayerTileName + "_ACTOR");

	if (0 >= PlayerTiles.size())
	{
		CurTileMap = UpTileGrid;
		PlayerTiles = GetPlayerTile(UpTileGrid, PlayerTileName + "_ACTOR");
		if (0 >= PlayerTiles.size())
		{
			return;
		}
	}

	MOVEDIR Dir = MOVEDIR::NONE;

	if (true == GameEngineInput::IsDown('D'))
	{
		Dir = MOVEDIR::RIGHT;

		if (PlayerTileName == "BABA")
		{
			// PlayerTiles[0].change
		}
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		Dir = MOVEDIR::LEFT;
	}

	if (true == GameEngineInput::IsDown('W'))
	{
		Dir = MOVEDIR::UP;
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		Dir = MOVEDIR::DOWN;
	}

	if (Dir == MOVEDIR::NONE)
	{
		return;
	}

	RuleInfo Rules;

	for (std::string Text : RuleSet)
	{
		Rules = GetRuleInfo(Text);

		// YOU ������ ���� ��� IsPlayerExist = false
		if (Rules.Behave == "STOP")
		{
			break;
		}
	}

	// ������ Ÿ���� �� Ȯ���ؾ��Ѵ�.

	// IsMoveTile();

	// return;

	for (size_t i = 0; i < PlayerTiles.size(); i++)
	{
		CurTileMap->LerpTile(PlayerTiles[i], Dir, BackGridPos);
	}

	return;

	//// RIGHT
	//if (true == GameEngineInput::IsDown('D'))
	//{
	//	// ������ Ÿ��
	//	NextTile = TileGrid->GetTile(Index_X + 1, Index_Y);

	//	if (nullptr != NextTile)
	//	{
	//		int Count = 0;

	//		// ���� Ÿ���� ���� ������ üũ
	//		while (nullptr != NextTile)
	//		{
	//			Count++;
	//			NextTile = TileGrid->GetTile(Index_X + Count, Index_Y);
	//		}

	//		// ���� Ÿ�� �� ���� �б�
	//		for (int i = Count; i >= 0; i--)
	//		{
	//			IsMove = TileGrid->LerpTile(Index_X + i, Index_Y, Index_X + i + 1, Index_Y, BackGridPos);
	//		}
	//	}

	//	else if (nullptr == NextTile)
	//	{
	//		IsMove = TileGrid->LerpTile(Index_X, Index_Y, Index_X + 1, Index_Y, BackGridPos);
	//	}


	//	// �ٹ� ��ġ, �ִϸ��̼� ����
	//	if (true == IsMove)
	//	{
	//		Index_X += 1;

	//		switch (BabaMoveStep)
	//		{
	//		case 0:
	//			MainRenderer->ChangeAnimation("Baba_Right");
	//			BabaMoveStep += 1;
	//			break;
	//		case 1:
	//			MainRenderer->ChangeAnimation("Baba_Right2");
	//			BabaMoveStep += 1;
	//			break;
	//		case 2:
	//			MainRenderer->ChangeAnimation("Baba_Right3");
	//			BabaMoveStep += 1;
	//			break;
	//		case 3:
	//			MainRenderer->ChangeAnimation("Baba_Right4");
	//			BabaMoveStep = 0;
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//// UP
	//else if (true == GameEngineInput::IsDown('W'))
	//{
	//	NextTile = TileGrid->GetTile(Index_X, Index_Y - 1);

	//	if (nullptr != NextTile)
	//	{
	//		int Count = 0;

	//		while (nullptr != NextTile)
	//		{
	//			Count++;
	//			NextTile = TileGrid->GetTile(Index_X, Index_Y - Count);
	//		}

	//		for (int i = Count; i >= 0; i--)
	//		{
	//			IsMove = TileGrid->LerpTile(Index_X, Index_Y - i, Index_X, Index_Y - i - 1, BackGridPos);
	//		}
	//	}

	//	else if (nullptr == NextTile)
	//	{
	//		IsMove = TileGrid->LerpTile(Index_X, Index_Y, Index_X, Index_Y - 1, BackGridPos);
	//	}

	//	if (true == IsMove)
	//	{
	//		Index_Y -= 1;

	//		switch (BabaMoveStep)
	//		{
	//		case 0:
	//			MainRenderer->ChangeAnimation("Baba_Up");
	//			BabaMoveStep += 1;
	//			break;
	//		case 1:
	//			MainRenderer->ChangeAnimation("Baba_Up2");
	//			BabaMoveStep += 1;
	//			break;
	//		case 2:
	//			MainRenderer->ChangeAnimation("Baba_Up3");
	//			BabaMoveStep += 1;
	//			break;
	//		case 3:
	//			MainRenderer->ChangeAnimation("Baba_Up4");
	//			BabaMoveStep = 0;
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//// LEFT
	//else if (true == GameEngineInput::IsDown('A'))
	//{
	//	// ���� Ÿ��
	//	NextTile = TileGrid->GetTile(Index_X - 1, Index_Y);

	//	if (nullptr != NextTile)
	//	{
	//		int Count = 0;

	//		while (nullptr != NextTile)
	//		{
	//			Count++;
	//			NextTile = TileGrid->GetTile(Index_X - Count, Index_Y);
	//		}

	//		for (int i = Count; i >= 0; i--)
	//		{
	//			IsMove = TileGrid->LerpTile(Index_X - i, Index_Y, Index_X - i - 1, Index_Y, BackGridPos);
	//		}
	//	}

	//	else if (nullptr == NextTile)
	//	{
	//		IsMove = TileGrid->LerpTile(Index_X, Index_Y, Index_X - 1, Index_Y, BackGridPos);
	//	}

	//	if (true == IsMove)
	//	{
	//		Index_X -= 1;

	//		switch (BabaMoveStep)
	//		{
	//		case 0:
	//			MainRenderer->ChangeAnimation("Baba_Left");
	//			BabaMoveStep += 1;
	//			break;
	//		case 1:
	//			MainRenderer->ChangeAnimation("Baba_Left2");
	//			BabaMoveStep += 1;
	//			break;
	//		case 2:
	//			MainRenderer->ChangeAnimation("Baba_Left3");
	//			BabaMoveStep += 1;
	//			break;
	//		case 3:
	//			MainRenderer->ChangeAnimation("Baba_Left4");
	//			BabaMoveStep = 0;
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//// DOWN
	//else if (true == GameEngineInput::IsDown('S'))
	//{
	//	// �Ʒ��� Ÿ��
	//	NextTile = TileGrid->GetTile(Index_X, Index_Y + 1);

	//	if (nullptr != NextTile)
	//	{
	//		int Count = 0;

	//		while (nullptr != NextTile)
	//		{
	//			Count++;
	//			NextTile = TileGrid->GetTile(Index_X, Index_Y + Count);
	//		}

	//		for (int i = Count; i >= 0; i--)
	//		{
	//			IsMove = TileGrid->LerpTile(Index_X, Index_Y + i, Index_X, Index_Y + i + 1, BackGridPos);
	//		}
	//	}

	//	else if (nullptr == NextTile)
	//	{
	//		IsMove = TileGrid->LerpTile(Index_X, Index_Y, Index_X, Index_Y + 1, BackGridPos);
	//	}

	//	if (true == IsMove)
	//	{
	//		Index_Y += 1;

	//		switch (BabaMoveStep)
	//		{
	//		case 0:
	//			MainRenderer->ChangeAnimation("Baba_Down");
	//			BabaMoveStep += 1;
	//			break;
	//		case 1:
	//			MainRenderer->ChangeAnimation("Baba_Down2");
	//			BabaMoveStep += 1;
	//			break;
	//		case 2:
	//			MainRenderer->ChangeAnimation("Baba_Down3");
	//			BabaMoveStep += 1;
	//			break;
	//		case 3:
	//			MainRenderer->ChangeAnimation("Baba_Down4");
	//			BabaMoveStep = 0;
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

}