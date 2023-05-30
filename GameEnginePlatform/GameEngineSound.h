#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

// 선언
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

class GameEngineSoundPlayer
{
	friend class GameEngineSound;

public:
	void SetVolume(float _Volume);
	void Stop();

	GameEngineSoundPlayer()
	{

	}


private:
	GameEngineSoundPlayer(FMOD::Channel* _Control)
		: Control(_Control)
	{
	}

	FMOD::Channel* Control = nullptr;
};

// 설명 :
class GameEngineSound
{
	static float GlobalVolume;

	// Management

	friend class SoundSystemCreator;
	friend class GameEngineSoundPlayer;

private:
	static std::map<std::string, GameEngineSound*> AllSound;

public:
	static void SetGlobalVolume(float _Value)
	{
		GlobalVolume = _Value;
	}

	static float GetGlobalVolume()
	{
		return GlobalVolume;
	}

	static void SoundLoad(const std::string& _Path)
	{
		GameEnginePath Path = _Path;
		SoundLoad(Path.GetFileName(), _Path);
	}

	static GameEngineSound* FindSound(const std::string& _Name);

	static void SoundLoad(const std::string& _Name, const std::string& _Path);

	// 1번의 재생을 하고 끝나면 그냥 종료하고 나는 컨트롤할수 없다.
	static GameEngineSoundPlayer SoundPlay(const std::string& _Name);

	static void Release();

	static void Update();

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
	FMOD::Sound* SoundHandle = nullptr;

	FMOD::Channel* Play();
	void Load(const std::string& _Path);

};
