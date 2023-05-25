#include "TitleLevel.h"

#include "Background_Black.h"
#include "TitleLogo.h"
#include "FadeAnimation.h"


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

}
void TitleLevel::Update(float _Delta)
{

}

