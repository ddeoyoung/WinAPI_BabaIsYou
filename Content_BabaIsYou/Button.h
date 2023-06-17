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


protected:

private:
	void Start();
	std::string FileName = "";

	class GameEngineRenderer* ButtonRender = nullptr;
	class GameEngineSprite* Texture = nullptr;

	float4 Scale = float4::ZERO;
};

