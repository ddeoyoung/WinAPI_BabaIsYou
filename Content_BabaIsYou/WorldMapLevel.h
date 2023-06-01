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
	// void Update(float _Delta) override;

	// ���
	class Background_Gray* BackgroundUI = nullptr;
	class Background_WorldMap* WorldMapUI = nullptr;

	// Ÿ�ϸ�
	class TileMap* TileObject = nullptr;

	// ���̵� �ִϸ��̼�
	class FadeAnimation* FadeUI = nullptr;
};

