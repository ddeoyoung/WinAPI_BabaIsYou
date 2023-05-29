#pragma once
#include <string>

// ����
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

// ���� :
class GameEngineSound
{
	// Management
public:
	// static void Init();

	static void SoundLoad(const std::string& _Name, const std::string& _Path);

	// 1���� ����� �ϰ� ������ �׳� �����ϰ� ���� ��Ʈ���Ҽ� ����.
	static void SoundPlay(const std::string& _Name);

	// 1���� ����� �ϰ� ���� Ư�� ���� �ȴ�.
	static void PlayBgm(const std::string& _Name);

	// Ư�� �����Ǵ� ���� ����� �����.
	static void StopBgm();


public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:

private:

};

