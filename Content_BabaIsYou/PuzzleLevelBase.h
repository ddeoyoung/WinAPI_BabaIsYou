#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
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

// ���� :
class PuzzleLevelBase : public GameEngineLevel
{
public:
	// constrcuter destructer
	PuzzleLevelBase();
	~PuzzleLevelBase();

	// delete Function
	PuzzleLevelBase(const PuzzleLevelBase& _Other) = delete;
	PuzzleLevelBase(PuzzleLevelBase&& _Other) noexcept = delete;
	PuzzleLevelBase& operator=(const PuzzleLevelBase& _Other) = delete;
	PuzzleLevelBase& operator=(PuzzleLevelBase&& _Other) noexcept = delete;

	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer EffectPlayer;

	void PuzzleLevelInit(std::string _DataText);

	void UpdateStringRuleCheck();
	void PlayerCheck();
	void MoveCheck();
	void WinCheck();

	void SinkCheck();

	std::vector<GameEngineRenderer*> GetPlayerTile(const std::string& _PlayerTileName);
	std::vector<GameEngineRenderer*> GetBreakTile(const std::string& _BreakTileName);
	std::vector<GameEngineRenderer*> GetWinTile(const std::string& _WinTileName);
	std::vector<GameEngineRenderer*> GetPushTile(const std::string& _PushTileName);
	std::vector<GameEngineRenderer*> GetSinkTile(const std::string& _SinkTileName);

	RuleInfo GetRuleInfo(const std::string& _Text);

	bool IsMoveTile(std::vector<GameEngineRenderer*> _PlayerTiles, std::vector<GameEngineRenderer*> _BreakTiles, MOVEDIR _Dir);

	void RuleTilePushRecursive(GameEngineRenderer* _Render, MOVEDIR _Dir, float4 Pos);
	void RuleTilePushRecursive(GameEngineRenderer* _Render, MOVEDIR _Dir, float4 Pos, int _GridNum);

	void ChangeBabaAnimation(MOVEDIR _Dir, const std::string& _AnimationName);

	void StageClearCheck();


	GameEngineRenderer* GetTileRenderer()
	{
		return TileRenderer;
	}

	std::vector<TileMap*> GetTileGrids()
	{
		return TileGrids;
	}

	float4 GetBackGridPos()
	{
		return BackGridPos;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;
	void Start() override;

private:

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
	std::string SinkTileName = "";

	std::set<std::string> SubjectSet;
	std::set<std::string> VerbSet;
	std::set<std::string> BehaveSet;

	std::set<std::string> RuleSet;

	std::vector<GameEngineRenderer*> PlayerTiles;
	std::vector<GameEngineRenderer*> BreakTiles;
	std::vector<GameEngineRenderer*> WinTiles;
	std::vector<GameEngineRenderer*> PushTiles;
	std::vector<GameEngineRenderer*> SinkTiles;

	std::vector<TileMap*> TileGrids;

	RuleInfo Rules;

	bool IsMove = false;
	bool IsPushMove = true;
	bool IsPlayerSink = false;
	bool IsPushSink = false;
	bool IsWin = false;
	bool IsCongratsUI = false;
	bool IsCongratsContUI = false;

	bool IsWinSound = false;

	float4 WinScale = { 0, 0 };
	float4 BackScale = { 0, 0 };
	float4 BackGridPos = { 0, 0 };

	float EffectInterval = 0.0f;

	class Background_Black* BackgroundUI_Black = nullptr;
	class Background_Gray* BackgroundUI_Gray = nullptr;

	class TileMap* PlayerTileMap = nullptr;

	class FadeAnimation* FadeUI = nullptr;
	class TextUI* Text = nullptr;
	class GameEngineWindowTexture* MapTexture = nullptr;
	class CongratsUI* Congratulations = nullptr;
	class Effect* TileEffect = nullptr;

	class Background_Pixel* MapDataImage = nullptr;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* TileRenderer = nullptr;
	GameEngineRenderer* TextRenderer = nullptr;

	GameEngineRenderer* NextTile = nullptr;
	GameEngineRenderer* CurTile = nullptr;

};

