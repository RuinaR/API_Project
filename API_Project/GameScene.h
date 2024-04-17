#pragma once
#include "Scene.h"
struct Animation;

class GameScene : public Scene
{
private:
	HBITMAP land;
	GameObject* obj1, * obj2, * obj3, * obj4, * obj5;
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

