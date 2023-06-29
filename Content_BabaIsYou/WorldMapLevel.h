#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <vector>

// Ό³Έν :
class TextUI;
class WorldMapLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	WorldMapLevel();
	~WorldMapLevel();

	// delete Function
	WorldMapLevel(const WorldMapLevel& _Other) = delete;
	WorldMapLevel(WorldMapLevel&& _Other) noexcept = delete;
	WorldMapLevel& operator=(const WorldMapLevel& _Other) = delete;
	WorldMapLevel& operator=(WorldMapLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	float4 BackGridPos = { 0, 0 };
	float4 StageTextScale = { 30, 30 };

	int SelectX = 9;
	int SelectY = 14;

	bool IsMove = false;
	bool IsStageSelect = false;

	std::string StageName = "";

	// Background
	class Background_Gray* BackgroundUI = nullptr;
	class Background_WorldMap* WorldMapUI = nullptr;

	// TileMap
	class TileMap* TileGrid = nullptr;
	class TileMap* NumberGrid = nullptr;
	class TileMap* SelectGrid = nullptr;

	GameEngineRenderer* TileRenderer = nullptr;
	GameEngineRenderer* NextTile = nullptr;

	// Fade Animation
	class FadeAnimation* FadeUI = nullptr;

	// WorldMapSelect
	class WorldMapSelect* SelectUI = nullptr;

	std::vector<TextUI*> StageTitle0;
	std::vector<TextUI*> StageTitle1;
	std::vector<TextUI*> StageTitle2;
	std::vector<TextUI*> StageTitle3;

	void MoveCheck();
	void StageTitleUI(int _SelectX, int _SelectY);
};

