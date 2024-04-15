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

#include "AnimationManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "MainFrame.h"
#include "WindowFrame.h"
#include "Mouse.h"
#include "Camera.h"
#include "Buffer.h"

#define TRANSCOLOR (RGB((255),(0),(255)))
#define COLSIZEOFFSET 0.5f

using namespace std;


