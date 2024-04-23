#include "pch.h"
#include "RestartBtn.h"
#include "GameScene.h"

void RestartBtn::Initialize()
{
	m_gameObj->SetTag("UIBTN");
	m_curColor = m_defaultColor;
}

void RestartBtn::Release()
{
}

void RestartBtn::Start()
{
}

void RestartBtn::Update()
{
	m_gameObj->SetPosition({
		m_UIPos.x + Camera::GetInstance()->GetPos().x,
		m_UIPos.y + Camera::GetInstance()->GetPos().y});

	RECT rect = {
	m_gameObj->Position().x - Camera::GetInstance()->GetPos().x,
	m_gameObj->Position().y - Camera::GetInstance()->GetPos().y,
	m_gameObj->Position().x - Camera::GetInstance()->GetPos().x + m_gameObj->Size().x,
	m_gameObj->Position().y - Camera::GetInstance()->GetPos().y + m_gameObj->Size().y };
	POINT point = { Mouse::GetInstance()->GetPos().X, Mouse::GetInstance()->GetPos().Y };
	if (!PtInRect(&rect, point))
		m_curColor = m_defaultColor;

	HBRUSH hBrush = CreateSolidBrush(m_curColor);
	FillRect(WindowFrame::GetInstance()->GetBuffer()->GetHDC(), &rect, hBrush);
	DeleteObject(hBrush);

}

void RestartBtn::OnLBtnDown()
{
	m_curColor = m_downColor;
}

void RestartBtn::OnLBtnUp()
{
	m_curColor = m_defaultColor;
	GameScene* newScene = new GameScene();
	WindowFrame::GetInstance()->SetScene(newScene);
}

void RestartBtn::OnRBtnDown()
{
}

void RestartBtn::OnRBtnUp()
{
}

void RestartBtn::OnMouseHover()
{
	m_curColor = m_hoverColor; 

	if (Mouse::GetInstance()->IsLeftDown())
		m_curColor = m_downColor;
}

void RestartBtn::SetUIPos(Vector2D v)
{
	m_UIPos = v;
}
