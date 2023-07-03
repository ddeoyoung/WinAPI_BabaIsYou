#pragma once

enum class UPDATE_ORDER
{
	BACKGROUND = 0,
	BACKGROUND_UI,
	PLAY,
};

enum class RENDER_ORDER
{
	BACKGROUND	= 0,
	BACKGROUND_UI,
	BACK_GRID,
	ACTOR_GRID,
	TEXT_GRID,
	PLAY,
	PLAY_UI,
	CONGRATS,
	FADE,
};

enum class COLLISION_ORDER
{
	BUTTON	= 0,
	CURSOR,
};

enum class TEXT_COLOR
{
	WHITE	= 0,
	PINK,
};

enum class BABA_DIR
{
	LEFT	= 0,
	RIGHT,
	UP,
	DOWN,
};