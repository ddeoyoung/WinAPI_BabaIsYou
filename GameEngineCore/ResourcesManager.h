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
class GameEngineTexture;
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
	// ���ο� static �����͵� ���̵� 1���� �д�.
	static ResourcesManager Inst;

	// �����ڸ� private�� �ִ´�.
	ResourcesManager();
	~ResourcesManager();

	std::map<std::string, GameEngineTexture*> AllTexture;
};

