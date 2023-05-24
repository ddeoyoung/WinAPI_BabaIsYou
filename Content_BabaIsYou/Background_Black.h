#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Background_Black : public GameEngineActor
{
public:
	// constrcuter destructer
	Background_Black();
	~Background_Black();

	// delete Function
	Background_Black(const Background_Black& _Other) = delete;
	Background_Black(Background_Black&& _Other) noexcept = delete;
	Background_Black& operator=(const Background_Black& _Other) = delete;
	Background_Black& operator=(Background_Black&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

};

