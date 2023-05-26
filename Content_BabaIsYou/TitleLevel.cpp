#include "TitleLevel.h"

#include "Background_Black.h"
#include "TitleLogo.h"
#include "FadeAnimation.h"
#include "Button.h"


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	TitleLogo* TitleLogoUI = CreateActor<TitleLogo>();
	Background_Black* BackgroundUI = CreateActor<Background_Black>();
	BackgroundUI->Init("Background_Black.bmp");

	Button* StartButton = CreateActor<Button>();
	StartButton->SetButton("StartButton.bmp");
	StartButton->SetPos({ 640, 450 });

	//Button* ExitButton = CreateActor<Button>();
	//ExitButton->SetButton("ExitButton.bmp");
	//ExitButton->SetPos({ 640, 750 });

}
void TitleLevel::Update(float _Delta)
{

}

