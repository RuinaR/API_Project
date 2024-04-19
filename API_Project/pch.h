#pragma once
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment (lib, "msimg32.lib")
#include <cmath>
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
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

using namespace std;


