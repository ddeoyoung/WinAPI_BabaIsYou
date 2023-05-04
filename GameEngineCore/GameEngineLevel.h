#pragma once
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include <list>
#include <map>

// 설명 : 화면(혹은 장면)을 표현한다.
// 타이틀 장면, 플레이 장면, 엔딩 장면 등
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		std::list<GameEngineActor*>& GroupList = AllActors[_Order];
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		GroupList.push_back(NewActor);
	}

protected:

private:

	// 맵
// 플레이어
// 몬스터

// -10번 std::list<> 액터 액터 액터 액터 
// 0번 std::list<> 액터 액터 액터 액터
// 1번 std::list<> 액터 액터 액터 액터

	std::map<int, std::list<GameEngineActor*>> AllActors;

	// Start Update Render
	void ActorInit(GameEngineActor* _Actor);
	void ActorUpdate(float _Delta);
	void ActorRender();
};

