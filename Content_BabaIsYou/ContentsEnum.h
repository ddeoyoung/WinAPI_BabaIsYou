#pragma once

enum class UpdateOrder
{
	BackGround = 0,
	BackGroundUI,
	Play,
};

enum class RenderOrder
{
	BackGround = 0,
	BackGroundUI,
	Grid,
	Play,
	PlayUI,
	Fade,
};

enum class CollisionOrder
{
	Button,
	Cursor,
};