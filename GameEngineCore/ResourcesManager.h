#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>


/*
	<�̱��� ����>
	1. �����ڸ� private�� �ִ´�
	2. private�� static �����͵� ���̵� 1���� �д�.
	3. �������ش�.

*/

// ���� :
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

	// �������ش�
	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	// ���ϸ��� �� ã������ �̸��� �ȴ�.
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

	// �������ִ� SpriteSheet �� �ڸ��� ���
	// _TexturePath ��ο� �����ϴ� �ؽ�ó�� �ε��ϰ� _SpriteName �̸��� ��������Ʈ�� �����
	GameEngineSprite* CreateSpriteSheet(const std::string& _TexturePath, int _XCount, int _YCount)
	{
		GameEnginePath Path = _TexturePath;
		return CreateSpriteSheet(Path.GetFileName(), _TexturePath, _XCount, _YCount);
	}

	GameEngineSprite* CreateSpriteSheet(const std::string& _SpriteName, const std::string& _TexturePath, int _XCount, int _YCount);



	bool IsLoadTexture(const std::string& _Image);


protected:

private:
	// ���ο� static �����͵� ���̵� 1���� �д�.
	static ResourcesManager Inst;

	// �����ڸ� private�� �ִ´�.
	ResourcesManager();
	~ResourcesManager();

	std::map<std::string, GameEngineWindowTexture*> AllTexture;
	std::map<std::string, GameEngineSprite*> AllSprite;

};

