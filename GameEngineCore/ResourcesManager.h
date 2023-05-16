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
class GameEngineSprite;
class GameEngineWindowTexture;
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
	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);

	GameEngineWindowTexture* FindTexture(const std::string& _Name);




	GameEngineSprite* FindSprite(const std::string& _Name);

	GameEngineSprite* CreateSpriteFolder(const std::string& _Path)
	{
		GameEnginePath FolderPath = _Path;
		return CreateSpriteFolder(FolderPath.GetFileName(), _Path);
	}

	GameEngineSprite* CreateSpriteFolder(const std::string& _SpriteName, const std::string& _Path);

	// 합쳐져있는 SpriteSheet 를 자르는 기능
	// _TexturePath 경로에 존재하는 텍스처를 로드하고 _SpriteName 이름의 스프라이트로 만들기
	GameEngineSprite* CreateSpriteSheet(const std::string& _TexturePath, int _XCount, int _YCount)
	{
		GameEnginePath Path = _TexturePath;
		return CreateSpriteSheet(Path.GetFileName(), _TexturePath, _XCount, _YCount);
	}

	GameEngineSprite* CreateSpriteSheet(const std::string& _SpriteName, const std::string& _TexturePath, int _XCount, int _YCount);



	bool IsLoadTexture(const std::string& _Image);


protected:

private:
	// 내부에 static 포인터든 값이든 1개를 둔다.
	static ResourcesManager Inst;

	// 생성자를 private에 넣는다.
	ResourcesManager();
	~ResourcesManager();

	std::map<std::string, GameEngineWindowTexture*> AllTexture;
	std::map<std::string, GameEngineSprite*> AllSprite;

};

