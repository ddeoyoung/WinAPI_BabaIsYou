#include "GameEnginePath.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::string& _path)
{
}

GameEnginePath::~GameEnginePath()
{
}

void GameEnginePath::GetCurrentPath()
{
	Path = std::filesystem::current_path();
}
