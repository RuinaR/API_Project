#include "pch.h"
#include "Collider.h"
set<Collider*>* Collider::SetCol()
{
	return m_ColObjSet;
}
void Collider::Start()
{
}
void Collider::Update()
{
}
Vector2D& Collider::ColSize()
{
	return m_colSize;
}
Vector2D& Collider::ColOffset()
{
	return m_colOffset;
}
void Collider::Initialize()
{
	ColInit();
	m_ColObjSet = new set<Collider*>();
	CollisionManager::GetInstance()->AddCollider(this);
	m_colSize.x *= COLSIZEOFFSET;
	m_colSize.y *= COLSIZEOFFSET;
}

void Collider::Release()
{
	m_ColObjSet->clear();
	delete m_ColObjSet;
	CollisionManager::GetInstance()->UnregisterCollider(this);
	ColRelease();
}

void Collider::DrawCollider()
{
	Vector2D leftTop = { m_colOffset.x + m_gameObj->Position().x - Camera::GetInstance()->GetPos().x,
		m_colOffset.y + m_gameObj->Position().y - Camera::GetInstance()->GetPos().y };
	Vector2D rightDown = { m_colOffset.x + m_gameObj->Position().x + m_colSize.x - Camera::GetInstance()->GetPos().x,
		m_colOffset.y + m_gameObj->Position().y + m_colSize.y - Camera::GetInstance()->GetPos().y };

	HPEN myPen, oldPen;
	HDC hdc = WindowFrame::GetInstance()->GetBuffer()->GetHDC();

	myPen = CreatePen(PS_SOLID, 3, DEBUGCOLOR);
	oldPen = (HPEN)SelectObject(hdc, myPen);

	MoveToEx(hdc, leftTop.x, leftTop.y, NULL);
	LineTo(hdc, rightDown.x, leftTop.y);
	MoveToEx(hdc, leftTop.x, leftTop.y, NULL);
	LineTo(hdc, leftTop.x, rightDown.y);
	MoveToEx(hdc, rightDown.x, rightDown.y, NULL);
	LineTo(hdc, leftTop.x, rightDown.y);
	MoveToEx(hdc, rightDown.x, rightDown.y, NULL);
	LineTo(hdc, rightDown.x, leftTop.y);

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
}

void Collider::SetTrigger(bool b)
{
	m_isTrigger = b;
}

bool Collider::GetTrigger()
{
	return m_isTrigger;
}

