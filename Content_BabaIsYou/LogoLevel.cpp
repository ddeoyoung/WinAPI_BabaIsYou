#include "LogoLevel.h"
#include "Logo.h"
#include "Background_Black.h"


LogoLevel::LogoLevel()
{
}

LogoLevel::~LogoLevel()
{
}

void LogoLevel::Start()
{
	Background_Black* Back = CreateActor<Background_Black>();
	Logo* LogoUI = CreateActor<Logo>();
}