#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Background_Pixel : public GameEngineActor
{
public:
	//friend GameEngineWindowTexture;

	// constrcuter destructer
	Background_Pixel();
	~Background_Pixel();

	// delete Function
	Background_Pixel(const Background_Pixel& _Other) = delete;
	Background_Pixel(Background_Pixel&& _Other) noexcept = delete;
	Background_Pixel& operator=(const Background_Pixel& _Other) = delete;
	Background_Pixel& operator=(Background_Pixel&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, float4 _Scale);
	void GetPixelColor(int _X, int _Y);

protected:

private:
	class GameEngineWindowTexture* Back = nullptr;
	class GameEngineRenderer* BackRender = nullptr;
};
