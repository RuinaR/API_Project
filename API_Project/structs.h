#pragma once
#include <vector>
#include <Windows.h>
using namespace std;
struct Vector2D
{
	float x = 0.0f;
	float y = 0.0f;
};

struct Animation
{
	vector<HBITMAP> bitmaps;
	float time;
	int identity;
};