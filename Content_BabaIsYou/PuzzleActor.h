#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:

private:
	void Start() override;

	GameEngineRenderer* PuzzleActorRender = nullptr;
};

