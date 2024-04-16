#pragma once
#include <Windows.h>

class Buffer
{
private:
	HWND m_hWnd;
	HBITMAP m_bitmap;
	HBITMAP m_oldBitmap;
	BITMAP m_bitInfo;
	HDC m_hdc;
public:
	Buffer();
	~Buffer();

	void Init(HWND hWnd);
	void Release();
	HBITMAP GetBitmap();
	BITMAP GetBitmapInfo();

	HDC GetHDC();
	void SetWihite();
	void CopyBitmap(HDC hdc);
};

