#include "pch.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	MainFrame::Create(hInstance);
	MainFrame::GetInstance()->Initialize(60);
	int result = MainFrame::GetInstance()->Run();
	MainFrame::Destroy();
	return result;
}