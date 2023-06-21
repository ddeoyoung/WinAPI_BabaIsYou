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


// Actor - 1.Type	2.Define	3. 

enum class ACTOR_TYPE
{
	NONE	= 0,
	ACTOR,
	SUBJECT_TEXT,
	VERB_TEXT,
	DEFINE_TEXT,
};

enum class ACTOR_DEFINE
{
	NONE	= 0,
	YOU,
	WIN,
	STOP,
	PUSH,
	DEFEAT,
};