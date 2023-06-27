#pragma once
#include <GameEngineCore/GameEngineLevel.h>
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

// Ό³Έν :
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

	std::set<std::string> SubjectSet;
	std::set<std::string> VerbSet;
	std::set<std::string> BehaveSet;

	std::set<std::string> RuleSet;

	std::vector<GameEngineRenderer*> PlayerTiles;

	bool IsTile = false;
	bool IsMove = false;
	bool IsSentence = false;

	float4 WinScale = { 0, 0 };
	float4 BackScale = { 840, 600 };
	float4 BackGridPos = { 0, 0 };

	class Background_Black* BackgroundUI_Black = nullptr;
	class Background_Gray* BackgroundUI_Gray = nullptr;

	class TileMap* TileGrid = nullptr;
	class TileMap* ActorGrid = nullptr;

	class FadeAnimation* FadeUI = nullptr;
	class TextUI* Text = nullptr;
	class GameEngineWindowTexture* MapTexture = nullptr;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* TileRenderer = nullptr;
	GameEngineRenderer* TextRenderer = nullptr;

	GameEngineRenderer* NextTile = nullptr;
	GameEngineRenderer* CurTile = nullptr;

	void UpdateStringRuleCheck();
	void MoveCheck();
	void WinCheck();

	std::vector<GameEngineRenderer*> GetPlayerTile(const std::string& _PlayerTileName);

	RuleInfo GetRuleInfo(const std::string& _Text);
};

