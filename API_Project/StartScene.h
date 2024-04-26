#pragma once
#include "Scene.h"
#include "StageMaker.h"
struct Animation;

class StartScene : public Scene
{
private:
	HBITMAP m_bg = NULL;
public:
	void Init() override;
	void Release() override;
	void Start() override;
};

