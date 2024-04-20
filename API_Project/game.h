#pragma once

#define UNITSIZE 100

#define TAG_LAND "land"
#define TAG_ATTACK "attack"
#define TAG_PLAYER "player"
#define TAG_CHANGE "change"
#define TAG_HIT "hit"
#define TAG_MONSTER "monster"


enum class PlayerArrow
{
	left,
	right,
	max
};

enum class PlayerAState
{
	idle,
	walk,
	jump,
	run,
	fly,
	eat_idle,
	eat_move,
	eat_jump,
	change,
	eat,
	eating,
	hit,
	attack,
	max
};

enum class PlayerMode
{
	mDefault,
	mSword,
	mStone,
	max
};

enum class MapType
{
	None = 0,
	Player = 1,
	Block = 2,
	DefaultMon = 3,
	SwordMon = 4,
	StoneMon = 5,
	max
};