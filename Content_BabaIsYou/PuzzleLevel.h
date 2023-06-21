#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <Windows.h>

// Ό³Έν :
class PuzzleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PuzzleLevel();
	~PuzzleLevel();

	// delete Function
	PuzzleLevel(const PuzzleLevel& _Other) = delete;
	PuzzleLevel(PuzzleLevel&& _Other) noexcept = delete;
	PuzzleLevel& operator=(const PuzzleLevel& _Other) = delete;
	PuzzleLevel& operator=(PuzzleLevel&& _Other) noexcept = delete;

	int You_X = 0;
	int You_Y = 0;

	float4 YouPos = { 0, 0 };



protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	float4 WinScale = { 0, 0 };
	float4 BackScale = { 840, 600 };
	float4 BackGridPos = { 0, 0 };

	class Background_Black* BackgroundUI_Black = nullptr;
	class Background_Gray* BackgroundUI_Gray = nullptr;

	class TileMap* TileGrid = nullptr;
	class TileMap* ActorGrid = nullptr;

	class FadeAnimation* FadeUI = nullptr;
	class TextUI* Text = nullptr;
	class GameEngineWindowTexture* MapTexture = nullptr;

	class Baba* Baba_Actor = nullptr;

	GameEngineRenderer* TileRenderer = nullptr;
	GameEngineRenderer* TextRenderer = nullptr;
};

