#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Background_Gray : public GameEngineActor
{
public:
	// constrcuter destructer
	Background_Gray();
	~Background_Gray();

	// delete Function
	Background_Gray(const Background_Gray& _Other) = delete;
	Background_Gray(Background_Gray&& _Other) noexcept = delete;
	Background_Gray& operator=(const Background_Gray& _Other) = delete;
	Background_Gray& operator=(Background_Gray&& _Other) noexcept = delete;

	void Init(const std::string& _FileName);

protected:

private:
	void Start() override;
	class GameEngineRenderer* BackRender = nullptr;
};

