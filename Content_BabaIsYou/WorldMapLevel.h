#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 :
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

	// 배경
	class Background_Gray* BackgroundUI = nullptr;
	class Background_WorldMap* WorldMapUI = nullptr;

	// 타일맵
	class TileMap* TileGrid = nullptr;
	GameEngineRenderer* TileRenderer = nullptr;

	class TileMap* NumberGrid = nullptr;
	GameEngineRenderer* NumberRenderer = nullptr;

	// 페이드 애니메이션
	class FadeAnimation* FadeUI = nullptr;
};

