#pragma once
#include "Scene.h"
#include "Edit.h"
struct Animation;

class EditerScene : public Scene
{
private:
	Edit* m_edit = nullptr;

public:
	void Init() override;
	void Release() override;
	void Start() override;
};

