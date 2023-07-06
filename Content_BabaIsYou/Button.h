#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRenderer.h>

// Ό³Έν :
class Button : public GameEngineActor
{
public:
	// constrcuter destructer
	Button();
	~Button();

	// delete Function
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

	void SetButton(const std::string& _ImageName);

	GameEngineCollision* Collision = nullptr;

	float4 GetScale()
	{
		return Scale;
	}

	class GameEngineRenderer* ButtonRender = nullptr;

protected:

private:
	void Start();
	std::string FileName = "";

	class GameEngineSprite* Texture = nullptr;

	float4 Scale = float4::ZERO;
};

