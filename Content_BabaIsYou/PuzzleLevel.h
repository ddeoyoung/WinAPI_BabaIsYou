#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/TileMap.h>
#include <Windows.h>
#include <string>
#include <set>
#include <vector>

class RuleInfo 
{
public:
	std::string Subject;
	std::string Verb;
	std::string Behave;
};

// 설명 :
class PuzzleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PuzzleLevel();
	~PuzzleLevel();

	// delete Function
	PuzzleLevel(const PuzzleLevel& _Other) = delete;
	PuzzleLevel(PuzzleLevel&& _Other) noexcept = delete;
	PuzzleLevel& operator=(const PuzzleLevel& _Other) = delete;
	PuzzleLevel& operator=(PuzzleLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;

	int BabaMoveStep = 0;

	std::string AnimationName = "";
	std::string TileName = "";

	std::string SubjectTileName = "";
	std::string VerbTileName = "";
	std::string BehaveTileName = "";

	std::string PlayerTileName = "";
	std::string BreakTileName = "";
	std::string WinTileName = "";

	std::set<std::string> SubjectSet;
	std::set<std::string> VerbSet;
	std::set<std::string> BehaveSet;

	std::set<std::string> RuleSet;

	std::vector<GameEngineRenderer*> PlayerTiles;
	std::vector<GameEngineRenderer*> BreakTiles;
	std::vector<GameEngineRenderer*> WinTiles;

	RuleInfo Rules;

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

	class TileMap* TileGrid = nullptr;
	class TileMap* UpTileGrid = nullptr;

	class TileMap* CurTileMap = nullptr;

	class FadeAnimation* FadeUI = nullptr;
	class TextUI* Text = nullptr;
	class GameEngineWindowTexture* MapTexture = nullptr;

	class CongratsUI* Congratulations = nullptr;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* TileRenderer = nullptr;
	GameEngineRenderer* TextRenderer = nullptr;

	GameEngineRenderer* NextTile = nullptr;
	GameEngineRenderer* CurTile = nullptr;


	RuleInfo GetRuleInfo(const std::string& _Text);

	void UpdateStringRuleCheck();
	void PlayerCheck();
	void MoveCheck();
	void WinCheck();

	// 다음 이동방향에 막히는 타일 체크
	bool IsMoveTile(std::vector<GameEngineRenderer*> _PlayerTiles, std::vector<GameEngineRenderer*> _BreakTiles, MOVEDIR _Dir);

	std::vector<GameEngineRenderer*> GetPlayerTile(TileMap* _TileMap, const std::string& _PlayerTileName);
	std::vector<GameEngineRenderer*> GetBreakTile(const std::string& _BreakTileName);
	std::vector<GameEngineRenderer*> GetWinTile(const std::string& _WinTileName);

};

