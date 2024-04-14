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

	void Init(HWND hWnd, float sizeRatioX, float sizeRatioY);
	void Release();
	HBITMAP GetBitmap();
	BITMAP GetBitmapInfo();

	void MakeHDC();
	HDC GetHDC();
	void SetWihite();
	void DeleteHDC();

	void CopyBitmap(HDC hdc);
	void CopyBitmapGame(HDC hdc, int x, int y);

};

