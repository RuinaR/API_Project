#pragma once

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