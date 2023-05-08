#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>


/*
	<싱글톤 패턴>
	1. 생성자를 private에 넣는다
	2. private에 static 포인터든 값이든 1개를 둔다.
	3. 리턴해준다.

*/

// 설명 :
class GameEngineTexture;
class ResourcesManager
{
public:
	// delete Function
	ResourcesManager(const ResourcesManager& _Other) = delete;
	ResourcesManager(ResourcesManager&& _Other) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager& _Other) = delete;
	ResourcesManager& operator=(ResourcesManager&& _Other) noexcept = delete;

	// 리턴해준다
	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	// 파일명이 곧 찾기위한 이름이 된다.
	void TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		TextureLoad(LoadPath.GetFileName(), _Path);
	}

	void TextureLoad(const std::string& _Name, const std::string& _Path);

	GameEngineTexture* FindTexture(const std::string& _Name);

	bool IsLoadTexture(const std::string& _Image);

protected:

private:
	// 내부에 static 포인터든 값이든 1개를 둔다.
	static ResourcesManager Inst;

	// 생성자를 private에 넣는다.
	ResourcesManager();
	~ResourcesManager();

	std::map<std::string, GameEngineTexture*> AllTexture;
};

