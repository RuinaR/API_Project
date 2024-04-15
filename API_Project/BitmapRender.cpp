#include "pch.h"
#include "BitmapRender.h"

void BitmapRender::DrawBitmap(HDC hdc, int x, int y, int w, int h, HBITMAP hbit, float angle, UINT transparentColor)
{
    // Convert angle to radians
    float rAngle = angle * 3.14159265358979323846f / 180.0f;

    // Create a memory DC for the bitmap
    HDC memDC = CreateCompatibleDC(hdc);
    if (memDC == NULL) {
        // Handle error
        return;
    }

    // Select the bitmap into the memory DC
    HGDIOBJ oldBitmap = SelectObject(memDC, hbit);
    if (oldBitmap == NULL) {
        // Handle error
        DeleteDC(memDC);
        return;
    }

    // Get the dimensions of the bitmap
    BITMAP bmp;
    GetObject(hbit, sizeof(BITMAP), &bmp);

    // Calculate the rotation center (center of the bitmap)
    POINT center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    // Set up the transformation matrix for rotation around the center
    XFORM xform;
    xform.eM11 = static_cast<FLOAT>(cos(rAngle));
    xform.eM12 = static_cast<FLOAT>(-sin(rAngle));
    xform.eM21 = static_cast<FLOAT>(sin(rAngle));
    xform.eM22 = static_cast<FLOAT>(cos(rAngle));
    xform.eDx = static_cast<FLOAT>(center.x * (1 - cos(rAngle)) - center.y * sin(rAngle) + x);
    xform.eDy = static_cast<FLOAT>(center.y * (1 - cos(rAngle)) + center.x * sin(rAngle) + y);


    // Apply transformation matrix
    SetGraphicsMode(hdc, GM_ADVANCED);
    SetWorldTransform(hdc, &xform);

    // Draw the rotated bitmap
    TransparentBlt(hdc, x, y, w, h, memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, transparentColor);

    // Reset world transform
    SetGraphicsMode(hdc, GM_COMPATIBLE);
    ModifyWorldTransform(hdc, NULL, MWT_IDENTITY);

    // Clean up
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}


BitmapRender::BitmapRender(HBITMAP hbit) : Component(), m_bit(hbit)
{
}

void BitmapRender::Initialize()
{
}

void BitmapRender::Release()
{
}

void BitmapRender::ChangeBitmap(HBITMAP hbit)
{
	m_bit = hbit;
}

void BitmapRender::Start()
{
}

void BitmapRender::Update()
{
	if (m_bit == NULL)
		return;
	Buffer* buffer = WindowFrame::GetInstance()->GetBuffer();
	buffer->MakeHDC();
	DrawBitmap(buffer->GetHDC(),
		m_gameObj->Position().x, m_gameObj->Position().y,
		m_gameObj->Size().x, m_gameObj->Size().y,
		m_bit, m_gameObj->Angle(), TRANSCOLOR);
	buffer->DeleteHDC();
}
