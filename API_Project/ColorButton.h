#pragma once

class ColorButton : public Component
{
protected:
	COLORREF m_defaultColor = RGB(255, 255, 255);
	COLORREF m_hoverColor = RGB(255, 255, 0);
	COLORREF m_downColor = RGB(0, 255, 0);
	COLORREF m_borderColor = RGB(0, 0, 0);
	COLORREF m_textColor = RGB(0, 0, 0);

	COLORREF m_curColor = NULL;
	Vector2D m_UIPos = Vector2D();
	Vector2D m_UISize = Vector2D();
	wstring m_text = wstring(TEXT(""));
	int m_textSize = 20;

	virtual void ButtonEvent();
public:
	void Initialize() override;
	void Release() override;
	void Start() override;
	void Update() override;

	void OnLBtnDown() final;
	void OnLBtnUp() final;
	void OnRBtnDown() final;
	void OnRBtnUp() final;
	void OnMouseHover() final;

	void SetUIPos(Vector2D v);
	void SetUISize(Vector2D v);
	void SetDefaultColor(COLORREF col);
	void SetHoverColor(COLORREF col);
	void SetDownColor(COLORREF col);
	void SetBorderColor(COLORREF col);
	void SetTextColor(COLORREF col);
	void SetTextSize(int val);
	void SetText(wstring str);
};

