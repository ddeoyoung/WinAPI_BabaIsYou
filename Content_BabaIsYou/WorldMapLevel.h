#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
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

	int Select_X = 0;
	int Select_Y = 0;

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

	// Fade Animation
	class FadeAnimation* FadeUI = nullptr;

	// TextUI
	class TextUI* Text = nullptr;

	// WorldMapSelect
	class WorldMapSelect* SelectUI = nullptr;
};

