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

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Start()
{

}

void TutorialLevel::LevelStart(GameEngineLevel* _PrevLevel)
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


	// MoveUI
	TutorialMoveUI = CreateActor<MoveUI>();

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
	// ������Ʈ
	TileGrid = CreateActor<TileMap>();
	TileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 2);
	TileGrid->SetLerpSpeed(10.0f);

	// �ؽ�Ʈ, �÷��̾�
	UpTileGrid = CreateActor<TileMap>();
	UpTileGrid->CreateTileMap("Actor.bmp", 21, 15, { 40 , 40 }, 3);
	UpTileGrid->SetLerpSpeed(10.0f);

	// �� ����
	// MapTexture - Tutorial
	Background_Pixel* MapDataImage = CreateActor<Background_Pixel>();
	MapDataImage->Init("Tutorial.bmp", { 850, 600 });
	MapTexture = ResourcesManager::GetInst().FindTexture("Tutorial.bmp");
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
				TileRenderer->ChangeAnimation("Baba_Right");

				MainRenderer = TileRenderer;
			}

			// ROCK_ACTOR
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 150, 0))
			{
				TileRenderer = TileGrid->SetTile(x, y, 734, BackGridPos);
				TileRenderer->SetName("ROCK_ACTOR");
				TileRenderer->CreateAnimationToFrame("ROCK_ACTOR", "Actor.bmp", { 734, 758, 782 }, 0.2f, true);
				TileRenderer->ChangeAnimation("ROCK_ACTOR");
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
				TileRenderer->CreateAnimationToFrame("WALL_OFF", "Actor.bmp", { 289, 313, 337 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("WALL");
			}

			// IS
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 200))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 792, BackGridPos);
				TileRenderer->SetName("IS");
				TileRenderer->CreateAnimationToFrame("IS", "Actor.bmp", { 792, 816, 840 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("IS_OFF", "Actor.bmp", { 793, 817, 841 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("IS");
			}

			// FLAG
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 200, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 726, BackGridPos);
				TileRenderer->SetName("FLAG");
				TileRenderer->CreateAnimationToFrame("FLAG", "Actor.bmp", { 726, 750, 774 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("FLAG_OFF", "Actor.bmp", { 727, 751, 775 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("FLAG");
			}

			// BABA
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(255, 100, 100))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 0, BackGridPos);
				TileRenderer->SetName("BABA");
				TileRenderer->CreateAnimationToFrame("BABA", "Actor.bmp", { 0, 24, 48 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("BABA_OFF", "Actor.bmp", { 1, 25, 49 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("BABA");
			}

			// YOU
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(100, 50, 50))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 864, BackGridPos);
				TileRenderer->SetName("YOU");
				TileRenderer->CreateAnimationToFrame("YOU", "Actor.bmp", { 864, 888, 912 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("YOU_OFF", "Actor.bmp", { 865, 889, 913 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("YOU");
			}

			// WIN
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 200, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 864, BackGridPos);
				TileRenderer->SetName("WIN");
				TileRenderer->CreateAnimationToFrame("WIN", "Actor.bmp", { 866, 890, 914 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("WIN_OFF", "Actor.bmp", { 867, 891, 915 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("WIN");
			}

			// STOP
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 100, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 868, BackGridPos);
				TileRenderer->SetName("STOP");
				TileRenderer->CreateAnimationToFrame("STOP", "Actor.bmp", { 868, 892, 916 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("STOP_OFF", "Actor.bmp", { 869, 893, 917 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("STOP");
			}

			// ROCK
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(200, 150, 0))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 732, BackGridPos);
				TileRenderer->SetName("ROCK");
				TileRenderer->CreateAnimationToFrame("ROCK", "Actor.bmp", { 732, 756, 780 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("ROCK_OFF", "Actor.bmp", { 733, 757, 781 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("ROCK");
			}

			// PUSH
			else if (MapTexture->GetColor(RGB(0, 0, 0), { fx, fy }) == RGB(0, 0, 200))
			{
				TileRenderer = UpTileGrid->SetTile(x, y, 870, BackGridPos);
				TileRenderer->SetName("PUSH");
				TileRenderer->CreateAnimationToFrame("PUSH", "Actor.bmp", { 870, 894, 918 }, 0.2f, true);
				TileRenderer->CreateAnimationToFrame("PUSH_OFF", "Actor.bmp", { 871, 895, 919 }, 0.2f, true); // Off
				TileRenderer->ChangeAnimation("PUSH");
			}
		}
	}
}

void TutorialLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TutorialLevel::Update(float _Delta)
{
	UpdateStringRuleCheck();

	MoveCheck();

	WinCheck();

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

	EffectInterval -= _Delta;
}

void TutorialLevel::UpdateStringRuleCheck()
{

	RuleSet.clear(); // �Ź� ����

	GameEngineRenderer* SubjectRenderer = nullptr;
	GameEngineRenderer* VerbRenderer = nullptr;
	GameEngineRenderer* BehaveRenderer = nullptr;

	std::set<GameEngineRenderer*> Renders;

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

				// �־� - Subject
				if (SubjectSet.contains(TileName))
				{
					SubjectTileName = TileName + " ";
					SubjectRenderer = CurTile;

					CurTile = UpTileGrid->GetTile(x, y + 1); // ���� ���� üũ

					if (nullptr != CurTile)
					{
						TileName = CurTile->GetName();

						// ���� - Verb
						if (VerbSet.contains(TileName))
						{
							VerbTileName = TileName + " ";
						}

						VerbRenderer = CurTile;

						// �ൿ - Behave
						CurTile = UpTileGrid->GetTile(x, y + 2);

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
									TutorialRuleInfo Info = GetTutorialRuleInfo(SubjectTileName + VerbTileName + BehaveTileName);

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


					CurTile = UpTileGrid->GetTile(x + 1, y); // ���� ���� üũ

					if (nullptr != CurTile)
					{
						TileName = CurTile->GetName();

						// ���� - Verb
						if (VerbSet.contains(TileName))
						{
							VerbTileName = TileName + " ";
						}

						VerbRenderer = CurTile;

						// �ൿ - Behave
						CurTile = UpTileGrid->GetTile(x + 2, y);

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
									TutorialRuleInfo Info = GetTutorialRuleInfo(SubjectTileName + VerbTileName + BehaveTileName);

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

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			CurTile = UpTileGrid->GetTile(x, y);

			if (nullptr == CurTile)
			{
				continue;
			}

			std::string TileName = CurTile->GetName();

			// �꿡 ���õ� Ÿ���ε���
			if (true == SubjectSet.contains(TileName) || true == VerbSet.contains(TileName) || true == BehaveSet.contains(TileName))
			{
				// �ϼ��� ���� ����µ� ������ ���� ���������� off ��Ų��.
				if (false == Renders.contains(CurTile))
				{
					CurTile->ChangeAnimation(TileName + "_OFF");
				}
			}
		}
	}


	return;
}


TutorialRuleInfo TutorialLevel::GetTutorialRuleInfo(const std::string& _Text)
{
	TutorialRuleInfo Return;

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


// �÷��̾ ������� ���ϴ� Ÿ�� ���� (= STOP)
std::vector<GameEngineRenderer*> TutorialLevel::GetBreakTile(const std::string& _BreakTileName)
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

// Player�ν� ������ �� �ִ� Ÿ�� ���� (= YOU)
std::vector<GameEngineRenderer*> TutorialLevel::GetPlayerTile(TileMap* _TileMap, const std::string& _PlayerTileName)
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

std::vector<GameEngineRenderer*> TutorialLevel::GetWinTile(const std::string& _WinTileName)
{
	WinTiles.clear();

	GameEngineRenderer* Tile = nullptr;
	std::string TileName = "";
	std::string WinTileName = _WinTileName;

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			// Win Ÿ���� TileGrid���� ����
			Tile = TileGrid->GetTile(x, y);

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


void TutorialLevel::WinCheck()
{
	TutorialRuleInfo Rules;

	// WIN�� ���Ե� ������ �ִ��� üũ
	for (std::string Text : RuleSet)
	{
		Rules = GetTutorialRuleInfo(Text);

		if (Rules.Behave == "WIN") // WIN ������ �ִ�
		{
			// Rules = �־�, IS, WIN
			WinTileName = Rules.Subject;

			WinTiles.clear();
			CurTileMap = TileGrid;
			WinTiles = GetWinTile(WinTileName + "_ACTOR");

			// PlayerTiles�� WinTiles�� ������ �������� Ŭ����
			PlayerCheck();

			for (size_t i = 0; i < PlayerTiles.size(); i++)
			{
				GameEngineRenderer* CheckTile = PlayerTiles[i];

				float4 HaflTileSize = CurTileMap->GetTileSize().Half();
				float4 TilePos = CheckTile->GetRenderPos();
				float4 TileIndex = CurTileMap->PosToIndex(TilePos - BackGridPos - HaflTileSize);

				int PlayerX = TileIndex.iX();
				int PlayerY = TileIndex.iY();

				for (size_t j = 0; j < WinTiles.size(); j++)
				{
					GameEngineRenderer* WinTile = WinTiles[j];
					float4 TilePos = WinTile->GetRenderPos();
					float4 TileIndex = CurTileMap->PosToIndex(TilePos - BackGridPos - HaflTileSize);
					float4 TileScale = { 35, 35 };

					int WinX = TileIndex.iX();
					int WinY = TileIndex.iY();


					// WinTiles�� ����Ʈ �߰�
					if (EffectInterval < 0)
					{
						TileEffect = CreateActor<Effect>();
						TileEffect->EffectRender->ChangeAnimation("FLAG_WIN");
						TileEffect->EffectRender->SetRenderPos(TilePos);
						TileEffect->EffectRender->SetRenderScale(TileScale);
					}

					// PlayerTile�� WinTile�� ����
					if (PlayerX == WinX && PlayerY == WinY)
					{
						// �������� Ŭ����
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


void TutorialLevel::PlayerCheck()
{
	TutorialRuleInfo Rules;

	// YOU�� ���Ե� ������ �ִ��� üũ
	for (std::string Text : RuleSet)
	{
		Rules = GetTutorialRuleInfo(Text);

		if (Rules.Behave == "YOU")
		{
			break;
		}
	}

	// ������ ���ӿ���
	if (Rules.Behave != "YOU")
	{
		return;
	}


	PlayerTiles.clear();
	CurTileMap = nullptr;

	// Player�ν� ������ �� �ִ� Ÿ�� üũ
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

bool TutorialLevel::IsMoveTile(std::vector<GameEngineRenderer*> _PlayerTiles, std::vector<GameEngineRenderer*> _BreakTiles, MOVEDIR _Dir)
{

	for (size_t i = 0; i < _PlayerTiles.size(); i++)
	{
		GameEngineRenderer* PlayerTile = _PlayerTiles[i];
		float4 TilePos = PlayerTile->GetRenderPos();
		float4 TileIndex = TileGrid->PosToIndex(TilePos);

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
			float4 TileIndex = TileGrid->PosToIndex(TilePos);

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


void TutorialLevel::MoveCheck()
{

	PlayerCheck();

	MOVEDIR Dir = MOVEDIR::NONE;

	if (true == GameEngineInput::IsDown('D'))
	{
		Dir = MOVEDIR::RIGHT;

		if (PlayerTileName == "BABA")
		{
			switch (BabaMoveStep)
			{
			case 0:
				PlayerTiles[0]->ChangeAnimation("Baba_Right");
				BabaMoveStep += 1;
				break;
			case 1:
				PlayerTiles[0]->ChangeAnimation("Baba_Right2");
				BabaMoveStep += 1;
				break;
			case 2:
				PlayerTiles[0]->ChangeAnimation("Baba_Right3");
				BabaMoveStep += 1;
				break;
			case 3:
				PlayerTiles[0]->ChangeAnimation("Baba_Right4");
				BabaMoveStep = 0;
				break;
			default:
				break;
			}
		}
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		Dir = MOVEDIR::LEFT;

		if (PlayerTileName == "BABA")
		{
			switch (BabaMoveStep)
			{
			case 0:
				PlayerTiles[0]->ChangeAnimation("Baba_Left");
				BabaMoveStep += 1;
				break;
			case 1:
				PlayerTiles[0]->ChangeAnimation("Baba_Left2");
				BabaMoveStep += 1;
				break;
			case 2:
				PlayerTiles[0]->ChangeAnimation("Baba_Left3");
				BabaMoveStep += 1;
				break;
			case 3:
				PlayerTiles[0]->ChangeAnimation("Baba_Left4");
				BabaMoveStep = 0;
				break;
			default:
				break;
			}
		}
	}

	if (true == GameEngineInput::IsDown('W'))
	{
		Dir = MOVEDIR::UP;

		if (PlayerTileName == "BABA")
		{
			switch (BabaMoveStep)
			{
			case 0:
				PlayerTiles[0]->ChangeAnimation("Baba_Up");
				BabaMoveStep += 1;
				break;
			case 1:
				PlayerTiles[0]->ChangeAnimation("Baba_Up2");
				BabaMoveStep += 1;
				break;
			case 2:
				PlayerTiles[0]->ChangeAnimation("Baba_Up3");
				BabaMoveStep += 1;
				break;
			case 3:
				PlayerTiles[0]->ChangeAnimation("Baba_Up4");
				BabaMoveStep = 0;
				break;
			default:
				break;
			}
		}
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		Dir = MOVEDIR::DOWN;

		if (PlayerTileName == "BABA")
		{
			switch (BabaMoveStep)
			{
			case 0:
				PlayerTiles[0]->ChangeAnimation("Baba_Down");
				BabaMoveStep += 1;
				break;
			case 1:
				PlayerTiles[0]->ChangeAnimation("Baba_Down");
				BabaMoveStep += 1;
				break;
			case 2:
				PlayerTiles[0]->ChangeAnimation("Baba_Down");
				BabaMoveStep += 1;
				break;
			case 3:
				PlayerTiles[0]->ChangeAnimation("Baba_Down");
				BabaMoveStep = 0;
				break;
			default:
				break;
			}
		}
	}

	if (Dir == MOVEDIR::NONE)
	{
		return;
	}



	// �÷��̾ ������� ���ϴ� Ÿ�� üũ
	for (std::string Text : RuleSet)
	{
		Rules = GetTutorialRuleInfo(Text);

		if (Rules.Behave == "STOP")
		{
			BreakTiles.clear();

			//				WALL
			BreakTileName = Rules.Subject;
			BreakTiles = GetBreakTile(BreakTileName + "_ACTOR");

			CurTileMap = UpTileGrid;

			IsMove = IsMoveTile(PlayerTiles, BreakTiles, Dir);

		}
	}

	// ������ ������ �� �ִ� ��� -> BreakTile�� �ƴ� Ÿ���� �ִٸ� �о�� ��
	if (true == IsMove)
	{
		for (size_t i = 0; i < PlayerTiles.size(); i++)
		{

			bool Check = false;
			GameEngineRenderer* CheckTile = PlayerTiles[i];

			float4 HaflTileSize = CurTileMap->GetTileSize().Half();
			float4 TilePos = CheckTile->GetRenderPos();
			float4 TileIndex = CurTileMap->PosToIndex(TilePos - BackGridPos - HaflTileSize); // �÷��̾�[i]�� �ε���

			// �о�� �ϴ� Ÿ���� ó�� ��ġ
			int FirstX = TileIndex.iX();
			int FirstY = TileIndex.iY();

			// �о�� �ϴ� Ÿ���� ���� ��ġ
			int SecondX = FirstX;
			int SecondY = FirstY;

			// �÷��̾� Ÿ�Ͽ� ����Ʈ �߰�
			float4 WalkDir = { 0, 0 };

			switch (Dir)
			{
			case MOVEDIR::LEFT:
				FirstX -= 1;
				SecondX -= 2;
				WalkDir = { 1, 0 };
				break;
			case MOVEDIR::RIGHT:
				FirstX += 1;
				SecondX += 2;
				WalkDir = { -1, 0 };
				break;
			case MOVEDIR::UP:
				FirstY -= 1;
				SecondY -= 2;
				WalkDir = { 0, 1 };
				break;
			case MOVEDIR::DOWN:
				FirstY += 1;
				SecondY += 2;
				WalkDir = { 0, -1 };
				break;
			case MOVEDIR::NONE:
				break;
			default:
				break;
			}

			// CurTileMap = UpTileGrid (�ؽ�Ʈ, �÷��̾� Ÿ��)
			GameEngineRenderer* NextTile;
			NextTile = CurTileMap->GetTile(FirstX, FirstY);

			// �̵��� ���� ��ġ�� Ÿ���� ���ٸ� �׳� �÷��̾ �̵�
			if (nullptr == NextTile)
			{
				CurTileMap->LerpTile(PlayerTiles[i], Dir, BackGridPos);
			}

			// �̵��� ���� ��ġ�� Ÿ���� ������
			else if (nullptr != NextTile)
			{
				// �о���� Ÿ���� ó��(First) ��ġ���� ����(Second) ��ġ�� �̵�
				CurTileMap->LerpTile(FirstX, FirstY, SecondX, SecondY, BackGridPos);
				CurTileMap->LerpTile(PlayerTiles[i], Dir, BackGridPos);
			}


			// �÷��̾� Ÿ�Ͽ� ����Ʈ �߰�
			TileEffect = CreateActor<Effect>();
			TileEffect->EffectRender->ChangeAnimation("BABA_WALK");
			TileEffect->SetDir(WalkDir);
			TileEffect->EffectRender->SetRenderPos(TilePos);
			TileEffect->EffectRender->SetRenderScale({ 35, 35 });

		}
	}

	else if (false == IsMove)
	{
		return;
	}
}
