#pragma once

class RestartBtn : public Component
{
private:
	COLORREF m_defaultColor = RGB(255, 255, 255);
	COLORREF m_hoverColor = RGB(255, 255, 0);
	COLORREF m_downColor = RGB(0, 255, 0);
	COLORREF m_curColor = NULL;
	Vector2D m_UIPos = Vector2D();
public:
	void Initialize() override;
	void Release() override;
	void Start() override;
	void Update() override;

	void OnLBtnDown() override;
	void OnLBtnUp() override;
	void OnRBtnDown() override;
	void OnRBtnUp() override;
	void OnMouseHover() override;

	void SetUIPos(Vector2D v);
};

