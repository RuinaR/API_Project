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
	Vector2D m_cameraPos = { 0.0f, 0.0f };
	Vector2D m_sizeRatio = {0.0f, 0.0f};
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

	Vector2D& SizeRatio();
	Vector2D& CameraPos();

	void CopyBitmap(HDC hdc);
};

