#pragma once
#include "Scene.h"
#include "Timer.h"
class MainFrame
{
private:
	static MainFrame* m_Pthis;
	Scene* m_scene = nullptr;
	MainFrame() {}
	~MainFrame() {}
	Timer m_timer;
	int m_targetFPS = 120;
public:
	static void Create(HINSTANCE hInstance);
	static MainFrame* GetInstance();
	static void Destroy();

	float DeltaTime();
	void Initialize(int targetFPS = 120);
	int Run();
private:
	void Release();
};