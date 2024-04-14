#pragma once

#include "AnimationRender.h"

static class AnimationManager
{
private:
	static bool IsBitmapFile(const string& filename);
public:
	static Animation LoadAnimation(const string& folderName, float time);
	static void ReleaseAnimation(Animation& anim);
};

