#pragma once
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment (lib, "msimg32.lib")
#include <cmath>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <vector>
#include <list>
#include <string>
#include <math.h>
#include <mmsystem.h>
#include <time.h>
#include <timeapi.h>

#include "AnimationManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "MainFrame.h"
#include "WindowFrame.h"
#include "Mouse.h"
#include "Camera.h"
#include "Buffer.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define TRANSCOLOR (RGB((255),(0),(255)))
#define COLSIZEOFFSET 1.0f
#define MAXWINDOWW 1920
#define MAXWINDOWH 1080
#define BUFFERBITW MAXWINDOWW
#define BUFFERBITH MAXWINDOWH
#define TARGETFPS 60

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
	max
};

using namespace std;


