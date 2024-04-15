#include "pch.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	MainFrame::Create(hInstance);
	MainFrame::GetInstance()->Initialize(240);
	int result = MainFrame::GetInstance()->Run();
	MainFrame::Destroy();
	return result;
}