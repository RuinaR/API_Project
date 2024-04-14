#include "pch.h"
CMouse* CMouse::mPthis = nullptr;

void CMouse::Create()
{
	if (!mPthis)
	{
		mPthis = new CMouse();
	}
}

CMouse* CMouse::GetInstance()
{
	return mPthis;
}

void CMouse::Destroy()
{
	if (mPthis)
	{
		delete mPthis;
		mPthis = nullptr;
	}
}

void CMouse::Initialize()
{
	this->mPos.X = 0;
	this->mPos.Y = 0;
	this->mIsLeftDown = false;
	this->mIsRightDown = false;
}

void CMouse::SetPos(int x, int y)
{
	this->mPos.X = x;
	this->mPos.Y = y;
}

void CMouse::SetPos(COORD pos)
{
	this->mPos = pos;
}

COORD CMouse::GetPos()
{
	return this->mPos;
}

void CMouse::SetLeftBtn(bool isDown)
{
	this->mIsLeftDown = isDown;
}

bool CMouse::IsLeftDown()
{
	return this->mIsLeftDown;
}

void CMouse::SetRightBtn(bool isDown)
{
	this->mIsRightDown = isDown;
}

bool CMouse::IsRightDown()
{
	return this->mIsRightDown;
}
