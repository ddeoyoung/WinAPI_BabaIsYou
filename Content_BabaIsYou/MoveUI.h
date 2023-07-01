#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MoveUI : public GameEngineActor
{
public:
	// constrcuter destructer
	MoveUI();
	~MoveUI();

	// delete Function
	MoveUI(const MoveUI& _Other) = delete;
	MoveUI(MoveUI&& _Other) noexcept = delete;
	MoveUI& operator=(const MoveUI& _Other) = delete;
	MoveUI& operator=(MoveUI&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	class GameEngineRenderer* Renderer = nullptr;
};

