#pragma once
class CMouse
{
private:
	static CMouse* mPthis;
	CMouse() {}
	~CMouse() {}

	COORD mPos = { 0 };
	bool mIsLeftDown = false;
	bool mIsRightDown = false;
public:
	static void Create();
	static CMouse* GetInstance();
	static void Destroy();

	void Initialize();

	void SetPos(int x, int y);
	void SetPos(COORD pos);
	COORD GetPos();
	void SetLeftBtn(bool isDown);
	bool IsLeftDown();
	void SetRightBtn(bool isDown);
	bool IsRightDown();
};