#pragma once
#include "Scene.h"
#include "StageMaker.h"
struct Animation;

class GameScene : public Scene
{
private:
	StageMaker* m_sMaker = nullptr;
public:
	void Init() override;
	void Release() override;
	void Start() override;

	void LBtnDown() override;
	void RBtnDown() override;
	void LBtnUp() override;
	void RBtnUp() override;
};

