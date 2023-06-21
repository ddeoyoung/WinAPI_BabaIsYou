#pragma once

enum class UpdateOrder
{
	BackGround	= 0,
	BackGroundUI,
	Play,
};

enum class RenderOrder
{
	BackGround	= 0,
	BackGroundUI,
	Grid,
	Play,
	PlayUI,
	Fade,
};

enum class CollisionOrder
{
	Button	= 0,
	Cursor,
};

enum class TextColor
{
	white	= 0,
	pink,
};


// Actor - 1.Type	2.Define	3. 

enum class ActorType
{
	Actor,
	Subject_Text,
	Verb_Text,
	Define_Text,
};

enum class ActorDefine
{
	You = 0,
	Win,
	Stop,

};