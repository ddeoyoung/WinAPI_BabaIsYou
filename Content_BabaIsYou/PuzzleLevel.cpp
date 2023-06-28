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
	// 오브젝트
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 2);
	TileGrid->SetLerpSpeed(10.0f);

	// 텍스트, 플레이어
	UpTileGrid = CreateActor<TileMap>();
	UpTileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 3);
	UpTileGrid->SetLerpSpeed(10.0f);


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
				TileRenderer = TileGrid->SetTile(x, y, 728, BackGridPos);
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

void PuzzleLevel::Update(float _Delta)
{
	UpdateStringRuleCheck();

	MoveCheck();
}



// < Stage 1 문장 조합 >
// 주어 : BABA, WALL, FLAG
// 동사 : IS
// 행동 : STOP, WIN, YOU

// 문장이 성립되는지 체크
// 문장 완성은 왼쪽->오른쪽, 위쪽->아래쪽만 가능
void PuzzleLevel::UpdateStringRuleCheck()
{

	RuleSet.clear(); // 매번 리셋

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

				// 주어 - Subject
				if (SubjectSet.contains(TileName))
				{
					SubjectTileName = TileName + " ";

					CurTile = UpTileGrid->GetTile(x, y + 1);

					if (nullptr != CurTile)
					{
						TileName = CurTile->GetName();

						// 동사 - Verb
						if (VerbSet.contains(TileName))
						{
							VerbTileName = TileName + " ";
						}

						// 행동 - Behave
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


RuleInfo PuzzleLevel::GetRuleInfo(const std::string& _Text)
{
	RuleInfo Return;

	// 문자열 자르기
	std::istringstream StringSplit(_Text);
	std::vector<std::string> ReturnTileNames;
	std::string ReturnTileName;

	while (getline(StringSplit, ReturnTileName, ' ')) //공백 단위로 구분
	{
		ReturnTileNames.push_back(ReturnTileName);
	}

	Return.Subject = ReturnTileNames[0];
	Return.Verb = ReturnTileNames[1];
	Return.Behave = ReturnTileNames[2];

	return Return;
}


// 플레이어가 통과하지 못하는 타일 집합 (= STOP)
std::vector<GameEngineRenderer*> PuzzleLevel::GetBreakTile(const std::string& _BreakTileName)
{

	GameEngineRenderer* Tile = nullptr;
	std::string TileName = "";

	BreakTiles.clear();

	// UpTileGrid
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			Tile = UpTileGrid->GetTile(x, y);

			if (nullptr != Tile)
			{
				TileName = Tile->GetName();

				if (TileName == _BreakTileName)
				{
					BreakTiles.push_back(Tile);
				}
			}
		}
	}

	// TileGrid
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			Tile = TileGrid->GetTile(x, y);

			if (nullptr != Tile)
			{
				TileName = Tile->GetName();

				// WALL				WALL_ACTOR
				if (TileName == _BreakTileName)
				{
					BreakTiles.push_back(Tile);
				}
			}
		}
	}

	return BreakTiles;
}

// Player로써 움직일 수 있는 타일 집합 (= YOU)
std::vector<GameEngineRenderer*> PuzzleLevel::GetPlayerTile(TileMap* _TileMap, const std::string& _PlayerTileName)
{
	PlayerTiles.clear();

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

void PuzzleLevel::PlayerCheck()
{
	RuleInfo Rules;

	// YOU가 포함된 문장이 있는지 체크
	for (std::string Text : RuleSet)
	{
		Rules = GetRuleInfo(Text);

		// YOU 문장이 없을 경우 IsPlayerExist = false
		if (Rules.Behave == "YOU")
		{
			break;
		}
	}

	// 없으면 게임오버
	if (Rules.Behave != "YOU")
	{
		return;
	}


	//PlayerTiles.clear();
	//CurTileMap = nullptr;

	// Player로써 움직일 수 있는 타일 체크
	PlayerTileName = Rules.Subject;
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


}

bool PuzzleLevel::IsMoveTile(std::vector<GameEngineRenderer*> _PlayerTiles, std::vector<GameEngineRenderer*> _BreakTiles, MOVEDIR _Dir)
{

	for (size_t i = 0; i < _PlayerTiles.size(); i++)
	{
		GameEngineRenderer* PlayerTile = _PlayerTiles[i];
		float4 TilePos = PlayerTile->GetRenderPos();
		float4 TileIndex = TileGrid->PosToIndex(TilePos);

		int Playerx = TileIndex.iX();
		int Playery = TileIndex.iY();

		switch (_Dir)
		{
		case MOVEDIR::LEFT:
			Playerx -= 1;
			break;
		case MOVEDIR::RIGHT:
			Playerx += 1;
			break;
		case MOVEDIR::UP:
			Playery -= 1;
			break;
		case MOVEDIR::DOWN:
			Playery += 1;
			break;
		case MOVEDIR::NONE:
			return true;
		default:
			break;
		}

		for (size_t j = 0; j < _BreakTiles.size(); j++)
		{
			GameEngineRenderer* BreakTile = _BreakTiles[j];
			float4 TilePos = BreakTile->GetRenderPos();
			float4 TileIndex = TileGrid->PosToIndex(TilePos);

			int Breakx = TileIndex.iX();
			int Breaky = TileIndex.iY();


			if (Playerx == Breakx && Playery == Breaky)
			{
				return false;
			}

		}
	}

	return true;
}

void PuzzleLevel::WinCheck()
{
	
}


void PuzzleLevel::MoveCheck()
{

	PlayerCheck();

	MOVEDIR Dir = MOVEDIR::NONE;

	if (true == GameEngineInput::IsDown('D'))
	{
		Dir = MOVEDIR::RIGHT;

		if (PlayerTileName == "BABA")
		{
			PlayerTiles[0]->ChangeAnimation("Baba_Right");
		}
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		Dir = MOVEDIR::LEFT;

		if (PlayerTileName == "BABA")
		{
			PlayerTiles[0]->ChangeAnimation("Baba_Left");
		}
	}

	if (true == GameEngineInput::IsDown('W'))
	{
		Dir = MOVEDIR::UP;

		if (PlayerTileName == "BABA")
		{
			PlayerTiles[0]->ChangeAnimation("Baba_Up");
		}
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		Dir = MOVEDIR::DOWN;

		if (PlayerTileName == "BABA")
		{
			PlayerTiles[0]->ChangeAnimation("Baba_Down");
		}
	}

	if (Dir == MOVEDIR::NONE)
	{
		return;
	}



	// 플레이어가 통과하지 못하는 타일 체크
	for (std::string Text : RuleSet)
	{
		Rules = GetRuleInfo(Text);

		if (Rules.Behave == "STOP")
		{
			break;
		}
	}

	//				WALL
	BreakTileName = Rules.Subject;
	BreakTiles = GetBreakTile(BreakTileName + "_ACTOR");

	CurTileMap = UpTileGrid;



	// 여기까지 잘되는거 확인

	// PlayerTiles가 이동할 자리에 BreakTile이 있으면 이동불가
	
	IsMove = IsMoveTile(PlayerTiles, BreakTiles, Dir);

	if (true == IsMove)
	{
		for (size_t i = 0; i < PlayerTiles.size(); i++)
		{
			CurTileMap->LerpTile(PlayerTiles[i], Dir, BackGridPos);
		}
	}



}