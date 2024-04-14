#include "pch.h"
#include "Collider.h"
vector<Collider*>* Collider::VecCol()
{
	return m_ColObjVec;
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
void Collider::Initialize()
{
	ColInit();
	m_ColObjVec = new vector<Collider*>();
	CollisionManager::GetInstance()->AddCollider(this);
	m_colSize.x *= COLSIZEOFFSET;
	m_colSize.y *= COLSIZEOFFSET;
}

void Collider::Release()
{
	m_ColObjVec->clear();
	delete m_ColObjVec;
	CollisionManager::GetInstance()->UnregisterCollider(this);
	ColRelease();
}

void Collider::SetCol(int w, int h)
{
	m_colSize.x = w;
	m_colSize.y = h;
}
