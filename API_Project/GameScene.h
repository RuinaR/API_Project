#pragma once
#include "Scene.h"
struct Animation;

class GameScene : public Scene
{
private:
	HBITMAP land;
	GameObject* player = nullptr;
public:
	void Init() override;
	void Release() override;
	void Start() override;

	void LBtnDown() override;
	void RBtnDown() override;
	void LBtnUp() override;
	void RBtnUp() override;
};

