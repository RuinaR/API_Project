#include "pch.h"
#include "Scene.h"
//test
#include "GameScene.h"

WindowFrame* WindowFrame::m_Pthis = nullptr;

void WindowFrame::Create(HINSTANCE hInstance)
{
	if (!m_Pthis)
	{
		m_Pthis = new WindowFrame();
		m_Pthis->m_Instance = hInstance;
		m_Pthis->m_buffer = new Buffer();
	}
}

WindowFrame* WindowFrame::GetInstance()
{
	return m_Pthis;
}

void WindowFrame::Destroy()
{
	if (m_Pthis)
	{
		delete m_Pthis->m_buffer;
		delete m_Pthis;
		m_Pthis = nullptr;
	}
}

LRESULT WindowFrame::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
		Mouse::GetInstance()->SetLeftBtn(true);
		Mouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		if (m_Pthis->m_scene)m_Pthis->m_scene->LBtnDown();
		return 0;
	case WM_LBUTTONUP:
		Mouse::GetInstance()->SetLeftBtn(false);
		Mouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		if (m_Pthis->m_scene)m_Pthis->m_scene->LBtnUp();
		return 0;
	case WM_RBUTTONDOWN:
		Mouse::GetInstance()->SetRightBtn(true);
		Mouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		if (m_Pthis->m_scene)m_Pthis->m_scene->RBtnDown();
		return 0;
	case WM_RBUTTONUP:
		Mouse::GetInstance()->SetRightBtn(false);
		Mouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		if (m_Pthis->m_scene)m_Pthis->m_scene->RBtnUp();
		return 0;
	case WM_MOUSEMOVE:
		Mouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_KILLFOCUS:
		m_Pthis->m_isFocus = false;

		//테스트용, 나중에 지울것
		SetFocus(WindowFrame::GetInstance()->GetHWND());
		return 0;
	case WM_SETFOCUS:
		MainFrame::GetInstance()->Timer().tick();
		MainFrame::GetInstance()->Timer().resetTotalDeltaTime();
		m_Pthis->m_isFocus = true;
		return 0;
	case WM_SIZE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		m_Pthis->m_buffer->CopyBitmap(hdc);
		m_Pthis->m_buffer->SetWihite();
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		m_Pthis->m_buffer->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void WindowFrame::SetScene(Scene* scene)
{
	if (m_scene)
	{
		m_scene->Release();
		delete m_scene;
	}
	m_scene = scene;
}

void WindowFrame::Initialize()
{
	BuildWindow();
	m_Pthis->m_buffer->Init(m_Pthis->m_hWnd);
	MoveWindow(m_Pthis->m_hWnd, 100, 100, 1440, 900, TRUE);
	SetFocus(m_Pthis->m_hWnd);
}

void WindowFrame::BuildWindow()
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = m_Pthis->m_Instance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("최원준");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	m_Pthis->m_hWnd =
		CreateWindow(WndClass.lpszClassName, WndClass.lpszClassName,
			WS_OVERLAPPEDWINDOW,
			0, 0, MAXWINDOWW, MAXWINDOWH,
			NULL, (HMENU)NULL, m_Pthis->m_Instance, NULL);

	ShowWindow(m_Pthis->m_hWnd, SW_SHOW);
}

void WindowFrame::Run(const MSG* Message)
{
	TranslateMessage(Message);
	DispatchMessage(Message);
}
