#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <Windows.h>

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

	class TileMap* TileGrid = nullptr;
	GameEngineRenderer* TileRenderer = nullptr;
};

