#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Cursor : public GameEngineActor
{
public:
	// constrcuter destructer
	Cursor();
	~Cursor();

	// delete Function
	Cursor(const Cursor& _Other) = delete;
	Cursor(Cursor&& _Other) noexcept = delete;
	Cursor& operator=(const Cursor& _Other) = delete;
	Cursor& operator=(Cursor&& _Other) noexcept = delete;

	static Cursor* MainCursor;

	float4 GetCursorPos();

	GameEngineCollision* GetCursorCollision()
	{
		return CursorCollision;
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	float4 CursorPos = float4::ZERO;

	class GameEngineRenderer* CursorRender = nullptr;
	class GameEngineCollision* CursorCollision = nullptr;
};

