#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class WorldMapSelect : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapSelect();
	~WorldMapSelect();

	// delete Function
	WorldMapSelect(const WorldMapSelect& _Other) = delete;
	WorldMapSelect(WorldMapSelect&& _Other) noexcept = delete;
	WorldMapSelect& operator=(const WorldMapSelect& _Other) = delete;
	WorldMapSelect& operator=(WorldMapSelect&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};

