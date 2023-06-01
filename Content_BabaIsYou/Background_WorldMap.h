#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Background_WorldMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Background_WorldMap();
	~Background_WorldMap();

	// delete Function
	Background_WorldMap(const Background_WorldMap& _Other) = delete;
	Background_WorldMap(Background_WorldMap&& _Other) noexcept = delete;
	Background_WorldMap& operator=(const Background_WorldMap& _Other) = delete;
	Background_WorldMap& operator=(Background_WorldMap&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	class GameEngineRenderer* BackRender = nullptr;
};

