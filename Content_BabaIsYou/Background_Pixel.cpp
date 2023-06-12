#include "Background_Pixel.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include "ContentsEnum.h"

Background_Pixel::Background_Pixel()
{
}

Background_Pixel::~Background_Pixel()
{
}

void Background_Pixel::Init(const std::string& _FileName, float4 _Scale)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	}

	Back = ResourcesManager::GetInst().FindTexture(_FileName);
	BackRender = CreateRenderer(_FileName, 5);
	BackRender->SetRenderScale(_Scale);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale().Half();
	SetPos(WinScale);

	//Back->GetColor;
}

//void GetPixelColor(GameEngineWindowTexture* _Image, float4 _Pos)
//{
//	GameEngineWindowTexture* MapImage = _Image;
//	HDC ImageDC = MapImage->GetImageDC();
//
//	return GetPixel(ImageDC, _Pos.iX(), _Pos.iY());
//}