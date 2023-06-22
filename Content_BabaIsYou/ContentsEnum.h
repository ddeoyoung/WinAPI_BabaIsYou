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
	GRID,
	PLAY,
	PLAY_UI,
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
	PICK,
};

enum class ACTOR_TYPE
{
	NONE	= 0,
	ACTOR,
	SUBJECT_TEXT,
	VERB_TEXT,
	BEHAVE_TEXT,
};

enum class ACTOR_BEHAVE
{
	NONE	= 0,
	YOU,
	WIN,
	STOP,
	PUSH,
	DEFEAT,
};

enum class BABA_DIR
{
	LEFT	= 0,
	RIGHT,
	UP,
	DOWN,
};