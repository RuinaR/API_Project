#pragma once
#include "Scene.h"
struct Animation;

class GameScene : public Scene
{
private:
	Animation anim;
	Animation land;
	GameObject* obj1, * obj2, * obj3 = nullptr;
public:
	void Init() override;
	void Release() override;
	void Start() override;

	void LBtnDown() override;
	void RBtnDown() override;
	void LBtnUp() override;
	void RBtnUp() override;
};

