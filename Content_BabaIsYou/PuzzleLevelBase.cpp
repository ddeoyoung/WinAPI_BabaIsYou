#include "PuzzleLevelBase.h"
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

#include <sstream>

PuzzleLevelBase::PuzzleLevelBase()
{
	SubjectSet.insert("BABA");
	SubjectSet.insert("WALL");
	SubjectSet.insert("FLAG");
	SubjectSet.insert("ROCK");

	VerbSet.insert("IS");

	BehaveSet.insert("YOU");
	BehaveSet.insert("PUSH");
	BehaveSet.insert("STOP");
	BehaveSet.insert("WIN");
}

PuzzleLevelBase::~PuzzleLevelBase()
{
}

void PuzzleLevelBase::Start()
{

}

void PuzzleLevelBase::PuzzleLevelInit(std::string _DataText)
{
	// Background
	BackgroundUI_Gray = CreateActor<Background_Gray>();
	BackgroundUI_Gray->Init("Background_Gray.bmp");
	BackgroundUI_Black = CreateActor<Background_Black>();
	BackgroundUI_Black->Init("Background_Black.bmp", { 850, 600 });

	// Fade Animation
	FadeUI = CreateActor<FadeAnimation>();
	FadeUI->FadeIn();

	// CongratsUI
	Congratulations = CreateActor<CongratsUI>();
	Congratulations->Off();

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
	BackScale = { 840, 600 };
	BackGridPos = { WinScale.X - (BackScale.X / 2), WinScale.Y - (BackScale.Y / 2) };

	// 21 x 15 개의 타일맵 생성
	{
		// 배경 타일
		TileMap* TileGrid = CreateActor<TileMap>();
		TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, (int)RENDER_ORDER::BACK_GRID);
		TileGrid->SetLerpSpeed(10.0f);

		TileGrids.push_back(TileGrid);
	}

	{
		// 오브젝트 타일
		TileMap* TileGrid = CreateActor<TileMap>();
		TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, (int)RENDER_ORDER::ACTOR_GRID);
		TileGrid->SetLerpSpeed(10.0f);

		TileGrids.push_back(TileGrid);
	}

	{
		// 텍스트, 플레이어 타일
		TileMap* TileGrid = CreateActor<TileMap>();
		TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, (int)RENDER_ORDER::TEXT_GRID);
		TileGrid->SetLerpSpeed(10.0f);

		TileGrids.push_back(TileGrid);
	}



	// 맵 세팅
	// MapTexture
	Background_Pixel* MapDataImage = CreateActor<Background_Pixel>();
	MapDataImage->Init(_DataText, { 850, 600 });
	MapTexture = ResourcesManager::GetInst().FindTexture(_DataText);
	MapDataImage->Off();

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			float fx = static_cast<float>(x);
			float fy = static_cast<float>(y);

			// WALL_ACTOR
			if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 0, 0))
			{
				TileRenderer = TileGrids[1]->SetTile(x, y, 290, BackGridPos);
				TileRenderer->SetName("WALL_ACTOR");
				TileRenderer->CreateAnimationToFrame("WALL_ACTOR", "Actor.bmp", { 290, 314, 338 }, 0.2f, true);
				TileRenderer->ChangeAnimation("WALL_ACTOR");
			}

			// BABA_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 0))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 2, BackGridPos);
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
				TileRenderer->ChangeAnimation("Baba_Right");
			}

			// ROCK_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 150, 0))
			{
				TileRenderer = TileGrids[1]->SetTile(x, y, 734, BackGridPos);
				TileRenderer->SetName("ROCK_ACTOR");
				TileRenderer->CreateAnimationToFrame("ROCK_ACTOR", "Actor.bmp", { 734, 758, 782 }, 0.2f, true);
				TileRenderer->ChangeAnimation("ROCK_ACTOR");
			}

			// BLOCK_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 100))
			{
				TileRenderer = TileGrids[0]->SetTile(x, y, 737, BackGridPos);
				TileRenderer->SetName("BLOCK_ACTOR");
				TileRenderer->CreateAnimationToFrame("BLOCK_ACTOR", "Actor.bmp", { 737, 761, 785 }, 0.2f, true);
				TileRenderer->ChangeAnimation("BLOCK_ACTOR");
			}

			// FLAG_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 255, 0))
			{
				TileRenderer = TileGrids[1]->SetTile(x, y, 728, BackGridPos);
				TileRenderer->SetName("FLAG_ACTOR");
				TileRenderer->CreateAnimationToFrame("FLAG_ACTOR", "Actor.bmp", { 728, 752, 776 }, 0.2f, true);
				TileRenderer->ChangeAnimation("FLAG_ACTOR");
			}

			// WALL
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(50, 50, 50))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 288, BackGridPos);
				TileRenderer->SetName("WALL");
				TileRenderer->CreateAnimationToFrame("WALL", "Actor.bmp", { 288, 312, 336 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("WALL_OFF", "Actor.bmp", { 289, 313, 337 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("WALL");
			}

			// IS
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 200))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 792, BackGridPos);
				TileRenderer->SetName("IS");
				TileRenderer->CreateAnimationToFrame("IS", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("IS_OFF", "Actor.bmp", { 793, 817, 841 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("IS");
			}

			// FLAG
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 200, 0))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 726, BackGridPos);
				TileRenderer->SetName("FLAG");
				TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("FLAG_OFF", "Actor.bmp", { 727, 751, 775 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("FLAG");
			}

			// BABA
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 100, 100))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 0, BackGridPos);
				TileRenderer->SetName("BABA");
				TileRenderer->CreateAnimationToFrame("BABA", "Actor.bmp", { 0, 24, 48 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("BABA_OFF", "Actor.bmp", { 1, 25, 49 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("BABA");
			}

			// YOU
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(100, 50, 50))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 864, BackGridPos);
				TileRenderer->SetName("YOU");
				TileRenderer->CreateAnimationToFrame("YOU", "Actor.bmp", { 864, 888, 912 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("YOU_OFF", "Actor.bmp", { 865, 889, 913 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("YOU");
			}

			// WIN
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 0))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 864, BackGridPos);
				TileRenderer->SetName("WIN");
				TileRenderer->CreateAnimationToFrame("WIN", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("WIN_OFF", "Actor.bmp", { 867, 891, 915 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("WIN");
			}

			// STOP
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 100, 0))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 868, BackGridPos);
				TileRenderer->SetName("STOP");
				TileRenderer->CreateAnimationToFrame("STOP", "Actor.bmp", { 868, 892, 916 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("STOP_OFF", "Actor.bmp", { 869, 893, 917 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("STOP");
			}

			// ROCK
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 150, 0))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 732, BackGridPos);
				TileRenderer->SetName("ROCK");
				TileRenderer->CreateAnimationToFrame("ROCK", "Actor.bmp", { 732, 756, 780 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("ROCK_OFF", "Actor.bmp", { 733, 757, 781 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("ROCK");
			}

			// PUSH
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 200))
			{
				TileRenderer = TileGrids[2]->SetTile(x, y, 870, BackGridPos);
				TileRenderer->SetName("PUSH");
				TileRenderer->CreateAnimationToFrame("PUSH", "Actor.bmp", { 870, 894, 918 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("PUSH_OFF", "Actor.bmp", { 871, 895, 919 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("PUSH");
			}
		}
	}
}

void PuzzleLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PuzzleLevelBase::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeUI->Off();
}

void PuzzleLevelBase::Update(float _Delta)
{
	UpdateStringRuleCheck();

	MoveCheck();

	WinCheck();

	StageClearCheck();

	EffectInterval -= _Delta;
}

void PuzzleLevelBase::UpdateStringRuleCheck()
{
	RuleSet.clear();

	GameEngineRenderer* SubjectRenderer = nullptr;
	GameEngineRenderer* VerbRenderer = nullptr;
	GameEngineRenderer* BehaveRenderer = nullptr;

	std::set<GameEngineRenderer*> Renders;

	GameEngineRenderer* CurTile = nullptr;
	std::string TileName = "";

	for (size_t i = 0; i < TileGrids.size(); i++)
	{
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 21; x++)
			{
				std::string SubjectTileName = "";
				std::string VerbTileName = "";
				std::string BehaveTileName = "";

				CurTile = TileGrids[i]->GetTile(x, y);

				if (nullptr != CurTile)
				{
					TileName = CurTile->GetName();

					// 주어 - Subject
					if (SubjectSet.contains(TileName))
					{
						SubjectTileName = TileName + " ";
						SubjectRenderer = CurTile;

						CurTile = TileGrids[i]->GetTile(x, y + 1); // 세로 문장 체크

						if (nullptr != CurTile)
						{
							TileName = CurTile->GetName();

							// 동사 - Verb
							if (VerbSet.contains(TileName))
							{
								VerbTileName = TileName + " ";
							}

							VerbRenderer = CurTile;

							// 행동 - Behave
							CurTile = TileGrids[i]->GetTile(x, y + 2);

							if (nullptr != CurTile)
							{
								TileName = CurTile->GetName();

								if (BehaveSet.contains(TileName))
								{
									BehaveTileName = TileName;
									BehaveRenderer = CurTile;

									RuleSet.insert(SubjectTileName + VerbTileName + BehaveTileName);

									if (nullptr != SubjectRenderer && nullptr != VerbRenderer && nullptr != BehaveRenderer)
									{
										RuleInfo Info = GetRuleInfo(SubjectTileName + VerbTileName + BehaveTileName);

										Renders.insert(SubjectRenderer);
										Renders.insert(VerbRenderer);
										Renders.insert(BehaveRenderer);

										SubjectRenderer->ChangeAnimation(Info.Subject);
										VerbRenderer->ChangeAnimation(Info.Verb);
										BehaveRenderer->ChangeAnimation(Info.Behave);
									}
								}
							}
						}


						CurTile = TileGrids[i]->GetTile(x + 1, y); // 가로 문장 체크

						if (nullptr != CurTile)
						{
							TileName = CurTile->GetName();

							// 동사 - Verb
							if (VerbSet.contains(TileName))
							{
								VerbTileName = TileName + " ";
							}

							VerbRenderer = CurTile;

							// 행동 - Behave
							CurTile = TileGrids[i]->GetTile(x + 2, y);

							if (nullptr != CurTile)
							{
								TileName = CurTile->GetName();

								if (BehaveSet.contains(TileName))
								{
									BehaveTileName = TileName;
									BehaveRenderer = CurTile;
									RuleSet.insert(SubjectTileName + VerbTileName + BehaveTileName);


									if (nullptr != SubjectRenderer && nullptr != VerbRenderer && nullptr != BehaveRenderer)
									{
										RuleInfo Info = GetRuleInfo(SubjectTileName + VerbTileName + BehaveTileName);

										Renders.insert(SubjectRenderer);
										Renders.insert(VerbRenderer);
										Renders.insert(BehaveRenderer);

										SubjectRenderer->ChangeAnimation(Info.Subject);
										VerbRenderer->ChangeAnimation(Info.Verb);
										BehaveRenderer->ChangeAnimation(Info.Behave);
									}


								}

							}
						}


					}

				}

			}
		}
	}

	// 완성된 문장이 아닌 텍스트 타일 - 애니메이션 Off
	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			CurTile = TileGrids[2]->GetTile(x, y);

			if (nullptr == CurTile)
			{
				continue;
			}

			std::string TileName = CurTile->GetName();

			if (true == SubjectSet.contains(TileName) || true == VerbSet.contains(TileName) || true == BehaveSet.contains(TileName))
			{
				if (false == Renders.contains(CurTile))
				{
					CurTile->ChangeAnimation(TileName + "_OFF");
				}
			}
		}
	}

	
	return;
}


RuleInfo PuzzleLevelBase::GetRuleInfo(const std::string& _Text)
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
std::vector<GameEngineRenderer*> PuzzleLevelBase::GetBreakTile(const std::string& _BreakTileName)
{

	GameEngineRenderer* Tile = nullptr;
	std::string TileName = "";

	BreakTiles.clear();

	for (size_t i = 0; i < TileGrids.size(); i++)
	{
		// UpTileGrid
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 21; x++)
			{
				Tile = TileGrids[i]->GetTile(x, y);

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

	}


	return BreakTiles;
}

// Player로써 움직일 수 있는 타일 집합 (= YOU)
std::vector<GameEngineRenderer*> PuzzleLevelBase::GetPlayerTile(const std::string& _PlayerTileName)
{
	PlayerTiles.clear();

	GameEngineRenderer* Tile = nullptr;
	std::string TileName = "";

	for (size_t i = 0; i < TileGrids.size(); i++)
	{
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 21; x++)
			{
				Tile = TileGrids[i]->GetTile(x, y);

				if (nullptr != Tile)
				{
					TileName = Tile->GetName();

					if (TileName == _PlayerTileName)
					{
						PlayerTiles.push_back(Tile);

						// 현재 플레이어가 있는 타일맵 번호
						PlayerTileMap = TileGrids[i];
					}
				}
			}
		}

	}
	return PlayerTiles;
}

std::vector<GameEngineRenderer*> PuzzleLevelBase::GetWinTile(const std::string& _WinTileName)
{
	WinTiles.clear();

	GameEngineRenderer* Tile = nullptr;
	std::string TileName = "";
	std::string WinTileName = _WinTileName;

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			// Win 타일은 TileGrid에만 존재
			Tile = TileGrids[1]->GetTile(x, y);

			if (nullptr != Tile)
			{
				TileName = Tile->GetName();

				if (TileName == WinTileName)
				{
					WinTiles.push_back(Tile);
				}
			}
		}
	}

	return WinTiles;
}


void PuzzleLevelBase::WinCheck()
{
	RuleInfo Rules;

	// WIN이 포함된 문장이 있는지 체크
	for (std::string Text : RuleSet)
	{
		Rules = GetRuleInfo(Text);

		if (Rules.Behave == "WIN")
		{
			// Rules = 주어, IS, WIN
			WinTileName = Rules.Subject;

			WinTiles.clear();
			WinTiles = GetWinTile(WinTileName + "_ACTOR");

			// PlayerTiles가 WinTiles에 닿으면 스테이지 클리어
			PlayerCheck();

			for (size_t i = 0; i < PlayerTiles.size(); i++)
			{
				GameEngineRenderer* CheckTile = PlayerTiles[i];

				float4 HaflTileSize = TileGrids[1]->GetTileSize().Half();
				float4 TilePos = CheckTile->GetRenderPos();
				float4 TileIndex = TileGrids[1]->PosToIndex(TilePos - BackGridPos - HaflTileSize);

				int PlayerX = TileIndex.iX();
				int PlayerY = TileIndex.iY();

				for (size_t j = 0; j < WinTiles.size(); j++)
				{
					GameEngineRenderer* WinTile = WinTiles[j];
					float4 TilePos = WinTile->GetRenderPos();
					float4 TileIndex = TileGrids[1]->PosToIndex(TilePos - BackGridPos - HaflTileSize);
					float4 TileScale = { 35, 35 };

					int WinX = TileIndex.iX();
					int WinY = TileIndex.iY();


					// WinTiles에 이펙트 추가
					if (EffectInterval < 0)
					{
						TileEffect = CreateActor<Effect>();
						TileEffect->EffectRender->ChangeAnimation("FLAG_WIN");
						TileEffect->EffectRender->SetRenderPos(TilePos);
						TileEffect->EffectRender->SetRenderScale(TileScale);
					}

					// PlayerTile이 WinTile에 닿음
					if (PlayerX == WinX && PlayerY == WinY)
					{
						// 스테이지 클리어
						IsWin = true;
					}

				}
			}
			if (EffectInterval < 0)
			{
				EffectInterval = 0.5f;
			}
			break;
		}
	}

}


void PuzzleLevelBase::PlayerCheck()
{
	RuleInfo Rules;

	for (std::string Text : RuleSet)
	{
		Rules = GetRuleInfo(Text);

		// YOU가 포함된 문장이 있는지 체크
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

	PlayerTiles.clear();

	// Player로써 움직일 수 있는 타일 저장
	PlayerTileName = Rules.Subject;
	PlayerTiles = GetPlayerTile(PlayerTileName + "_ACTOR");
}

bool PuzzleLevelBase::IsMoveTile(std::vector<GameEngineRenderer*> _PlayerTiles, std::vector<GameEngineRenderer*> _BreakTiles, MOVEDIR _Dir)
{
	for (size_t i = 0; i < _PlayerTiles.size(); i++)
	{
		GameEngineRenderer* PlayerTile = _PlayerTiles[i];
		float4 TilePos = PlayerTile->GetRenderPos();
		float4 TileIndex = TileGrids[1]->PosToIndex(TilePos);

		int PlayerX = TileIndex.iX();
		int PlayerY = TileIndex.iY();

		switch (_Dir)
		{
		case MOVEDIR::LEFT:
			PlayerX -= 1;
			break;
		case MOVEDIR::RIGHT:
			PlayerX += 1;
			break;
		case MOVEDIR::UP:
			PlayerY -= 1;
			break;
		case MOVEDIR::DOWN:
			PlayerY += 1;
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
			float4 TileIndex = TileGrids[1]->PosToIndex(TilePos);

			int BreakX = TileIndex.iX();
			int BreakY = TileIndex.iY();


			if (PlayerX == BreakX && PlayerY == BreakY)
			{
				return false;
			}
		}
	}

	return true;
}


void PuzzleLevelBase::MoveCheck()
{
	PlayerCheck();

	MOVEDIR Dir = MOVEDIR::NONE;

	if (true == GameEngineInput::IsDown('D'))
	{
		Dir = MOVEDIR::RIGHT;

		if (PlayerTileName == "BABA")
		{
			ChangeBabaAnimation(Dir, "Right");
		}
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		Dir = MOVEDIR::LEFT;

		if (PlayerTileName == "BABA")
		{
			ChangeBabaAnimation(Dir, "Left");
		}
	}

	if (true == GameEngineInput::IsDown('W'))
	{
		Dir = MOVEDIR::UP;

		if (PlayerTileName == "BABA")
		{
			ChangeBabaAnimation(Dir, "Up");
		}
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		Dir = MOVEDIR::DOWN;

		if (PlayerTileName == "BABA")
		{
			ChangeBabaAnimation(Dir, "Down");
		}
	}

	if (Dir == MOVEDIR::NONE)
	{
		return;
	}


	// 문장 체크
	for (std::string Text : RuleSet)
	{
		Rules = GetRuleInfo(Text);

		// 플레이어가 통과하지 못하는 타일 체크
		if (Rules.Behave == "STOP")
		{
			BreakTiles.clear();

			BreakTileName = Rules.Subject;
			BreakTiles = GetBreakTile(BreakTileName + "_ACTOR");

			IsMove = IsMoveTile(PlayerTiles, BreakTiles, Dir);
		}

		// 플레이어가 PUSH 할 수 있는 타일 체크
		if (Rules.Behave == "PUSH")
		{
			PushTiles.clear();
			
			PushTileName = Rules.Subject;
			PushTiles = GetPushTile(PushTileName + "_ACTOR");

			IsPushMove = IsMoveTile(PlayerTiles, PushTiles, Dir);
		}
	}

	// 무조건 움직일 수 있는 경우 
	// BreakTile이 아닌 타일
	// PushTile인 타일
	if (true == IsMove)
	{
		for (size_t i = 0; i < PlayerTiles.size(); i++)
		{
			bool Check = false;
			GameEngineRenderer* CheckTile = PlayerTiles[i];

			float4 TileSize = TileGrids[1]->GetTileSize().Half();
			float4 TilePos = CheckTile->GetRenderPos();
			float4 TileIndex = TileGrids[1]->PosToIndex(TilePos - BackGridPos - TileSize); // 플레이어[i]의 인덱스

			// 밀어야 하는 타일의 처음 위치
			int TileX = TileIndex.iX();
			int TileY = TileIndex.iY();

			// 플레이어 이펙트 방향
			float4 EffectDir = { 0, 0 };

			switch (Dir)
			{
			case MOVEDIR::LEFT:
				TileX -= 1;
				EffectDir = { 1, 0 };
				break;
			case MOVEDIR::RIGHT:
				TileX += 1;
				EffectDir = { -1, 0 };
				break;
			case MOVEDIR::UP:
				TileY -= 1;
				EffectDir = { 0, 1 };
				break;
			case MOVEDIR::DOWN:
				TileY += 1;
				EffectDir = { 0, -1 };
				break;
			case MOVEDIR::NONE:
				break;
			default:
				break;
			}

			// 나는 일단 무조건 움직여야 한다.
			//TileGrids[2]->LerpTile(PlayerTiles[i], Dir, BackGridPos);
			PlayerTileMap->LerpTile(PlayerTiles[i], Dir, BackGridPos);

			{
				// 글자 타일들 체크
				GameEngineRenderer* NextTile;
				NextTile = TileGrids[2]->GetTile(TileX, TileY);
				if (NextTile != nullptr)
				{
					RuleTilePushRecursive(NextTile, Dir, BackGridPos, 2);
				}
			}

			{
				// PUSH 타일들 체크
				GameEngineRenderer* NextTile;
				NextTile = TileGrids[1]->GetTile(TileX, TileY);

				for (size_t j = 0; j < PushTiles.size(); j++)
				{
					if (NextTile == PushTiles[j])
					{
						if (false == IsPushMove)
						{
							//TileGrids[1]->LerpTile(PushTiles[j], Dir, BackGridPos);
							RuleTilePushRecursive(NextTile, Dir, BackGridPos, 1);
						}
					}
				}
			}

			// 플레이어 타일에 이펙트 추가
			TileEffect = CreateActor<Effect>();
			TileEffect->EffectRender->ChangeAnimation("BABA_WALK");
			TileEffect->SetDir(EffectDir);
			TileEffect->EffectRender->SetRenderPos(TilePos);
			TileEffect->EffectRender->SetRenderScale({ 35, 35 });

		}
	}

	else if (false == IsMove)
	{
		return;
	}
}

// Push가 가능한 오브젝트 타일들 집합
std::vector<GameEngineRenderer*> PuzzleLevelBase::GetPushTile(const std::string& _PushTileName)
{
	PushTiles.clear();

	GameEngineRenderer* Tile = nullptr;
	std::string TileName = "";
	std::string PushTileName = _PushTileName;

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			// PUSH가 가능한 오브젝트 타일은 TileGrid에만 존재
			Tile = TileGrids[1]->GetTile(x, y);

			if (nullptr != Tile)
			{
				TileName = Tile->GetName();

				if (TileName == PushTileName)
				{
					PushTiles.push_back(Tile);
				}
			}
		}
	}

	return PushTiles;
}

void PuzzleLevelBase::RuleTilePushRecursive(GameEngineRenderer* _Render, MOVEDIR _Dir, float4 _Pos)
{
	float4 PushDir = { 0, 0 };

	switch (_Dir)
	{
	case MOVEDIR::LEFT:
		PushDir = { -1, 0 };
		break;
	case MOVEDIR::RIGHT:
		PushDir = { 1, 0 };
		break;
	case MOVEDIR::UP:
		PushDir = { 0, -1 };
		break;
	case MOVEDIR::DOWN:
		PushDir = { 0, 1 };
		break;
	case MOVEDIR::NONE:
		break;
	default:
		break;
	}

	TileGrids[2]->LerpTile(_Render, _Dir, _Pos);

	float4 TextTileSize = TileGrids[2]->GetTileSize();
	float4 TextTileIndex = TileGrids[2]->PosToIndex(_Render->GetRenderPos() - _Pos - TextTileSize.Half());
	TextTileIndex += PushDir;

	GameEngineRenderer* TextTile;
	TextTile = TileGrids[2]->GetTile(TextTileIndex.iX(), TextTileIndex.iY());
	if (TextTile == nullptr)
	{
		return;
	}


	RuleTilePushRecursive(TextTile, _Dir, _Pos);
}

void PuzzleLevelBase::RuleTilePushRecursive(GameEngineRenderer* _Render, MOVEDIR _Dir, float4 _Pos, int _GridNum)
{
	float4 PushDir = { 0, 0 };

	switch (_Dir)
	{
	case MOVEDIR::LEFT:
		PushDir = { -1, 0 };
		break;
	case MOVEDIR::RIGHT:
		PushDir = { 1, 0 };
		break;
	case MOVEDIR::UP:
		PushDir = { 0, -1 };
		break;
	case MOVEDIR::DOWN:
		PushDir = { 0, 1 };
		break;
	case MOVEDIR::NONE:
		break;
	default:
		break;
	}

	int Num = _GridNum;

	TileGrids[Num]->LerpTile(_Render, _Dir, _Pos);

	float4 TextTileSize = TileGrids[Num]->GetTileSize();
	float4 TextTileIndex = TileGrids[Num]->PosToIndex(_Render->GetRenderPos() - _Pos - TextTileSize.Half());
	TextTileIndex += PushDir;

	GameEngineRenderer* TextTile;
	TextTile = TileGrids[Num]->GetTile(TextTileIndex.iX(), TextTileIndex.iY());

	if (TextTile == nullptr)
	{
		return;
	}


	RuleTilePushRecursive(TextTile, _Dir, _Pos, Num);
}


void PuzzleLevelBase::ChangeBabaAnimation(MOVEDIR _Dir, const std::string& _DirName)
{
	std::string AnimationName = "Baba_" + _DirName;

	switch (BabaMoveStep)
	{
	case 0:
		PlayerTiles[0]->ChangeAnimation(AnimationName);
		BabaMoveStep += 1;
		break;
	case 1:
		PlayerTiles[0]->ChangeAnimation(AnimationName + "2");
		BabaMoveStep += 1;
		break;
	case 2:
		PlayerTiles[0]->ChangeAnimation(AnimationName + "3");
		BabaMoveStep += 1;
		break;
	case 3:
		PlayerTiles[0]->ChangeAnimation(AnimationName + "4");
		BabaMoveStep = 0;
		break;
	default:
		break;
	}
}

// 스테이지 클리어 후 Congratulations
void PuzzleLevelBase::StageClearCheck()
{
	if (true == IsWin && false == IsCongratsUI)
	{
		Congratulations->On();
		Congratulations->CongratsRender->ChangeAnimation("Congrats");

		if (true == Congratulations->CongratsRender->IsAnimation("Congrats")
			&& true == Congratulations->CongratsRender->IsAnimationEnd())
		{
			Congratulations->CongratsRender->ChangeAnimation("CongratsCont");
			IsCongratsUI = true;
		}
	}

	if (true == IsCongratsUI
		&& true == Congratulations->CongratsRender->IsAnimation("CongratsCont")
		&& true == Congratulations->CongratsRender->IsAnimationEnd())
	{
		Congratulations->Off();
		FadeUI->FadeOut();
	}

	if (true == FadeUI->FadeRender->IsAnimation("FadeOut")
		&& true == FadeUI->FadeRender->IsAnimationEnd())
	{
		GameEngineCore::ChangeLevel("WorldMapLevel");
	}
}

//
//void PuzzleLevelBase::GetTiles()
//{
//	GameEngineRenderer* Tile = nullptr;
//	std::string TileName = "";
//
//
//	// 문장에 맞는 타일 저장
//	for (size_t i = 0; i < TileGrids.size(); i++)
//	{
//		for (int y = 0; y < 15; y++)
//		{
//			for (int x = 0; x < 21; x++)
//			{
//				Tile = TileGrids[i]->GetTile(x, y);
//
//				if (nullptr != Tile)
//				{
//					TileName = Tile->GetName();
//
//					if (Rules.Behave == "YOU" && TileName == Rules.Subject)
//					{
//						PlayerTiles.push_back(Tile);
//					}
//
//					else if (Rules.Behave == "WIN" && TileName == Rules.Subject)
//					{
//						WinTiles.push_back(Tile);
//					}
//
//					else if (Rules.Behave == "STOP" && TileName == Rules.Subject)
//					{
//						BreakTiles.push_back(Tile);
//					}
//
//					else if (Rules.Behave == "PUSH" && TileName == Rules.Subject)
//					{
//						PushTiles.push_back(Tile);
//					}
//				}
//			}
//		}
//	}
//}