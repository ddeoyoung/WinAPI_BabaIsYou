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

protected:

private:
	void Start();
	class GameEngineRenderer* ButtonRender = nullptr;
};

