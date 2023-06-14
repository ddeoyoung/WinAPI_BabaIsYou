#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
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

	// ���
	class Background_Gray* BackgroundUI = nullptr;
	class Background_WorldMap* WorldMapUI = nullptr;

	// Ÿ�ϸ�
	class TileMap* TileGrid = nullptr;
	GameEngineRenderer* TileRenderer = nullptr;

	class TileMap* NumberGrid = nullptr;
	GameEngineRenderer* NumberRenderer = nullptr;

	// ���̵� �ִϸ��̼�
	class FadeAnimation* FadeUI = nullptr;
};

