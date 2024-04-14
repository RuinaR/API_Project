#include "pch.h"
#include "Buffer.h"

Buffer::Buffer()
	:m_bitmap(NULL), m_hWnd(NULL), m_hdc(NULL), m_oldBitmap(NULL), m_bitInfo()
{

}

Buffer::~Buffer()
{

}

void Buffer::Init(HWND hWnd, float sizeRatioX, float sizeRatioY)
{
	m_hWnd = hWnd;
	RECT rect = { 0 };
	GetClientRect(m_hWnd, &rect);

	HDC hdcMain = GetDC(m_hWnd);
	m_hdc = CreateCompatibleDC(hdcMain);
	m_bitmap = CreateCompatibleBitmap(hdcMain, rect.right * sizeRatioX, rect.bottom * sizeRatioY);

	m_oldBitmap = (HBITMAP)SelectObject(m_hdc, m_bitmap);
	FillRect(m_hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	GetObject(m_bitmap, sizeof(BITMAP), &m_bitInfo);

	SelectObject(m_hdc, m_oldBitmap);
	DeleteDC(m_hdc);
	ReleaseDC(m_hWnd, hdcMain);
	m_hdc = NULL;
}

void Buffer::Release()
{
	DeleteObject(m_bitmap);
}

HBITMAP Buffer::GetBitmap()
{
	return m_bitmap;
}

BITMAP Buffer::GetBitmapInfo()
{
	return m_bitInfo;
}

void Buffer::MakeHDC()
{
	if (!m_hdc)
	{
		HDC hdcMain = GetDC(m_hWnd);
		m_hdc = CreateCompatibleDC(hdcMain);
		m_oldBitmap = (HBITMAP)SelectObject(m_hdc, m_bitmap);
		ReleaseDC(m_hWnd, hdcMain);
	}
}

HDC Buffer::GetHDC()
{
	return m_hdc;
}

void Buffer::SetWihite()
{
	MakeHDC();
	RECT rect;
	rect = { 0,0,m_bitInfo.bmWidth,m_bitInfo.bmHeight };
	FillRect(m_hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	DeleteHDC();
}

void Buffer::DeleteHDC()
{
	if (m_hdc)
	{
		SelectObject(m_hdc, m_oldBitmap);
		DeleteDC(m_hdc);
		m_hdc = NULL;
	}
}

void Buffer::CopyBitmap(HDC hdc)
{
	this->MakeHDC();
	BitBlt(hdc, 0, 0, m_bitInfo.bmWidth, m_bitInfo.bmHeight, this->GetHDC(), 0, 0, SRCCOPY);
	this->DeleteHDC();
}

void Buffer::CopyBitmapGame(HDC hdc, int x, int y)
{
	RECT rect;
	GetClientRect(m_hWnd, &rect);

	this->MakeHDC();
	BitBlt(hdc, 0, 0, m_bitInfo.bmWidth, m_bitInfo.bmHeight, this->GetHDC(), x - rect.right / 2, y - rect.bottom / 2, SRCCOPY);
	this->DeleteHDC();
}

