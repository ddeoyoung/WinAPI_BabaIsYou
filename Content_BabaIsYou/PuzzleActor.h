#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>

// Ό³Έν :
class PuzzleActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PuzzleActor();
	~PuzzleActor();

	// delete Function
	PuzzleActor(const PuzzleActor& _Other) = delete;
	PuzzleActor(PuzzleActor&& _Other) noexcept = delete;
	PuzzleActor& operator=(const PuzzleActor& _Other) = delete;
	PuzzleActor& operator=(PuzzleActor&& _Other) noexcept = delete;

	void SetPuzzle(const std::string& _AniamtionName, const std::vector<int>& _Index);

protected:

private:
	void Start() override;

	class TileMap* TileGrid = nullptr;

	GameEngineRenderer* TileRenderer = nullptr;
	GameEngineRenderer* PuzzleActorRender = nullptr;
};

