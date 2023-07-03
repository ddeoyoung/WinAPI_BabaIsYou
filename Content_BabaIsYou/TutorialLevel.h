#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/TileMap.h>
#include <Windows.h>
#include <string>
#include <set>
#include <vector>

#include "PuzzleLevel.h"

class TutorialRuleInfo
{
public:
	std::string Subject;
	std::string Verb;
	std::string Behave;
};

// Ό³Έν :
class TutorialLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TutorialLevel();
	~TutorialLevel();

	// delete Function
	TutorialLevel(const TutorialLevel& _Other) = delete;
	TutorialLevel(TutorialLevel&& _Other) noexcept = delete;
	TutorialLevel& operator=(const TutorialLevel& _Other) = delete;
	TutorialLevel& operator=(TutorialLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;

	int Index_X = 13;
	int Index_Y = 11;
	int BabaMoveStep = 0;

	std::string AnimationName = "";
	std::string TileName = "";

	std::string SubjectTileName = "";
	std::string VerbTileName = "";
	std::string BehaveTileName = "";

	std::string PlayerTileName = "";
	std::string BreakTileName = "";
	std::string WinTileName = "";
	std::string PushTileName = "";

	std::set<std::string> SubjectSet;
	std::set<std::string> VerbSet;
	std::set<std::string> BehaveSet;

	std::set<std::string> RuleSet;

	std::vector<GameEngineRenderer*> PlayerTiles;
	std::vector<GameEngineRenderer*> BreakTiles;
	std::vector<GameEngineRenderer*> WinTiles;
	std::vector<GameEngineRenderer*> PushTiles;

	TutorialRuleInfo Rules;

	bool IsTile = false;
	bool IsMove = false;
	bool IsWin = false;
	bool IsCongratsUI = false;
	bool IsCongratsContUI = false;

	float4 WinScale = { 0, 0 };
	float4 BackScale = { 840, 600 };
	float4 BackGridPos = { 0, 0 };

	float EffectInterval = 0.0f;

	class Background_Black* BackgroundUI_Black = nullptr;
	class Background_Gray* BackgroundUI_Gray = nullptr;

	//class TileMap* TileGrid = nullptr;
	//class TileMap* TileGrid = nullptr;
	//class TileMap* UpTileGrid = nullptr;

	class std::vector<TileMap*> TileGrids;

	class TileMap* CurTileMap = nullptr;

	class FadeAnimation* FadeUI = nullptr;
	class TextUI* Text = nullptr;
	class GameEngineWindowTexture* MapTexture = nullptr;

	class CongratsUI* Congratulations = nullptr;

	class Effect* TileEffect = nullptr;

	class MoveUI* TutorialMoveUI = nullptr;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* TileRenderer = nullptr;
	GameEngineRenderer* TextRenderer = nullptr;

	GameEngineRenderer* NextTile = nullptr;
	GameEngineRenderer* CurTile = nullptr;

	void ChangeBabaAnimation(MOVEDIR _Dir, const std::string& _AnimationName);

	TutorialRuleInfo GetTutorialRuleInfo(const std::string& _Text);

	void UpdateStringRuleCheck();
	void PlayerCheck();
	void MoveCheck();
	void WinCheck();

	bool IsMoveTile(std::vector<GameEngineRenderer*> _PlayerTiles, std::vector<GameEngineRenderer*> _BreakTiles, MOVEDIR _Dir);

	std::vector<GameEngineRenderer*> GetPlayerTile(const std::string& _PlayerTileName);
	std::vector<GameEngineRenderer*> GetBreakTile(const std::string& _BreakTileName);
	std::vector<GameEngineRenderer*> GetWinTile(const std::string& _WinTileName);
	std::vector<GameEngineRenderer*> GetPushTile(const std::string& _PushTileName);

	std::vector<GameEngineRenderer*> GetTiles(const std::string& _TileName, const std::string& _Behave);

	void RuleTilePushRecursive(GameEngineRenderer* _Render, MOVEDIR _Dir, float4 Pos);
};

