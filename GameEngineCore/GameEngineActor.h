#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <list>

// 설명 :
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	// 위치           
	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	float4 GetPos()
	{
		return Pos;
	}

	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, EnumType _Order)
	{
		return CreateRenderer(_ImageName, static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, int _Order);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}

protected:

private:
	GameEngineLevel* Level;

	float4 Pos = float4::ZERO;

	std::list<GameEngineRenderer*> AllRenderer;

	void PushMainCameraRenderer(GameEngineRenderer*);
};

