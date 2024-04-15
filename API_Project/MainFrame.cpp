#include "pch.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "GameScene.h"
#include <time.h>
MainFrame* MainFrame::m_Pthis = nullptr;

void MainFrame::Create(HINSTANCE hInstance)
{
	if (!m_Pthis)
	{
		m_Pthis = new MainFrame();
		WindowFrame::Create(hInstance);
		Mouse::Create();
		Camera::Create();
	}
}

MainFrame* MainFrame::GetInstance()
{
	return m_Pthis;
}

void MainFrame::Destroy()
{
	if (m_Pthis)
	{
		Camera::Destroy();
		Mouse::Destroy();
		WindowFrame::Destroy();
		delete m_Pthis;
		m_Pthis = nullptr;
	}
}

Timer& MainFrame::Timer()
{
	return m_timer;
}

float MainFrame::DeltaTime()
{
	return m_timer.getDeltaTime();
}

void MainFrame::Initialize(int targetFPS)
{
	m_targetFPS = targetFPS;
	WindowFrame::GetInstance()->Initialize();
	WindowFrame::GetInstance()->BuildWindow();
	ObjectManager::Create();
	CollisionManager::Create();
	m_scene = new GameScene();
	m_scene->Init();
	m_scene->Start();
	WindowFrame::GetInstance()->SetScene(m_scene);
}

int MainFrame::Run()
{
	MSG Message;
	double targetFrameTime = 1.0 / m_targetFPS;
	WCHAR strFPS[64];
	int frameCount = 0;
	int fps = 0;
	int frameOffset = 0;

	while (TRUE) {
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				Release();
				break;
			}
			WindowFrame::GetInstance()->Run(&Message);
		}
		else if(WindowFrame::GetInstance()->IsFocus())
		{
			m_timer.tick();
			if (m_timer.getDeltaTime() >= targetFrameTime)
			{
				frameCount++;
				//UPDATE
				ObjectManager::GetInstance()->Update();
				CollisionManager::GetInstance()->Update();
				//RENDER
				InvalidateRect(WindowFrame::GetInstance()->GetHWND(), NULL, FALSE);
				UpdateWindow(WindowFrame::GetInstance()->GetHWND());
				//1초마다 업데이트 프레임 계산 후 조정?
				if (m_timer.hasSecondPassed())
				{
					fps = frameCount;
					frameCount = 0;
					m_timer.resetElapsedTime();
					swprintf_s(strFPS, (int)_countof(strFPS), TEXT("FPS : %d / TargetFPS : %d / FPSOffset : %d"),
						fps, m_targetFPS, frameOffset);
					SetWindowText(WindowFrame::GetInstance()->GetHWND(), strFPS);
					//if (fps < m_targetFPS)
					//{
					//	frameOffset += (m_targetFPS - fps) * 0.5f;
					//	targetFrameTime = 1.0 / (m_targetFPS + frameOffset);
					//}
					//else if (fps > m_targetFPS)
					//{
					//	frameOffset -= (fps - m_targetFPS) * 0.5f;
					//	targetFrameTime = 1.0 / (m_targetFPS + frameOffset);
					//}
				}
			}
			else
			{
				DWORD sleepTime = DWORD((targetFrameTime - m_timer.getDeltaTime()) * 1000); // 밀리초로 변환
				Sleep(sleepTime);
			}
		}
	}

	return (int)Message.wParam;
}

void MainFrame::Release()
{
	m_scene->Release();
	delete m_scene;
	ObjectManager::GetInstance()->Release();
	ObjectManager::Destroy();
	CollisionManager::Destroy();
}
