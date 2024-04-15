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
		m_Pthis->m_hWnd = hWnd;
		m_Pthis->m_buffer->Init(hWnd, 1.0f, 1.0f);
		return 0;
	case WM_LBUTTONDOWN:
		CMouse::GetInstance()->SetLeftBtn(true);
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		if (m_Pthis->m_scene)m_Pthis->m_scene->LBtnDown();
		return 0;
	case WM_LBUTTONUP:
		CMouse::GetInstance()->SetLeftBtn(false);
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		if (m_Pthis->m_scene)m_Pthis->m_scene->LBtnUp();
		return 0;
	case WM_RBUTTONDOWN:
		CMouse::GetInstance()->SetRightBtn(true);
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		if (m_Pthis->m_scene)m_Pthis->m_scene->RBtnDown();
		return 0;
	case WM_RBUTTONUP:
		CMouse::GetInstance()->SetRightBtn(false);
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		if (m_Pthis->m_scene)m_Pthis->m_scene->RBtnUp();
		return 0;
	case WM_MOUSEMOVE:
		CMouse::GetInstance()->SetPos(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_KILLFOCUS:
		m_Pthis->m_isFocus = false;
		return 0;
	case WM_SETFOCUS:
		MainFrame::GetInstance()->Timer().tick();
		MainFrame::GetInstance()->Timer().resetElapsedTime();
		m_Pthis->m_isFocus = true;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		m_Pthis->m_buffer->CopyBitmap(hdc);
		m_Pthis->m_buffer->MakeHDC();
		Rectangle(m_Pthis->m_buffer->GetHDC(), 1, 1, 
			m_Pthis->m_buffer->GetBitmapInfo().bmWidth - 1, m_Pthis->m_buffer->GetBitmapInfo().bmHeight - 1);
		m_Pthis->m_buffer->DeleteHDC();
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

}

void WindowFrame::BuildWindow()
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = this->m_Instance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("ÃÖ¿øÁØ");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	this->m_hWnd =
		CreateWindow(WndClass.lpszClassName, WndClass.lpszClassName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, (HMENU)NULL, this->m_Instance, NULL);

	ShowWindow(this->m_hWnd, SW_SHOW);
}

void WindowFrame::Run(const MSG* Message)
{
	TranslateMessage(Message);
	DispatchMessage(Message);
}
