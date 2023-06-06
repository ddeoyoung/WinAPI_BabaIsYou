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

	void Init(const std::string& _FileName, float4 _Scale);


protected:

private:
	void Start() override;
	class GameEngineRenderer* BackRender = nullptr;

	class TileMap* TileGrid = nullptr;
};

