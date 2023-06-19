#include "Cursor.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "ContentsEnum.h"

Cursor* Cursor::MainCursor = nullptr;

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

void Cursor::Start()
{
	CursorCollision = CreateCollision(CollisionOrder::Cursor);
	CursorCollision->SetCollisionScale({50, 50});
}

void Cursor::Update(float _Delta)
{
	SetPos(GameEngineWindow::MainWindow.GetMousePos());
	CursorCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos());
}

float4 GetCursorPos()
{
	return GameEngineWindow::MainWindow.GetMousePos();
}