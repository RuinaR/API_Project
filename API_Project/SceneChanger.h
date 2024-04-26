#pragma once
#include "Component.h"
class SceneChanger : public Component
{
public:
	void Initialize() override;
	void Release() override;
	void Start() override;
	void Update() override;
public:
	void ChangeGameScene();
	void ChangeStartScene();
	void ChangeEditScene();
};

