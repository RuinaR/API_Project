#include "pch.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Component.h"

BOOL Rigidbody::SetNoIntersect(const LPRECT pHold, LPRECT pRect)
{
	RECT rcInter = { 0 };
	if (IntersectRect(&rcInter, pHold, pRect))
	{
		int nW = rcInter.right - rcInter.left;
		int nH = rcInter.bottom - rcInter.top;

		if (nW > nH)
		{
			if (rcInter.top == pHold->top)
			{
				pRect->top -= nH;
				pRect->bottom -= nH;
				m_velocity.y = 0.0f;
			}
			else if (rcInter.bottom == pHold->bottom)
			{
				pRect->top += nH;
				pRect->bottom += nH;
				m_velocity.y = 0.0f;
			}
		}
		else
		{
			if (rcInter.left == pHold->left)
			{
				pRect->left -= nW;
				pRect->right -= nW;
				m_velocity.x = 0.0f;
			}
			else if (rcInter.right == pHold->right)
			{
				pRect->left += nW;
				pRect->right += nW;
				m_velocity.x = 0.0f;
			}
		}
		return TRUE;
	}
	return FALSE;

}

void Rigidbody::Initialize()
{
	m_velocity = { 0.0f, 0.0f };
}

void Rigidbody::Release()
{
}

void Rigidbody::Start()
{
	m_box = m_gameObj->GetComponent<BoxCollider>();
}

void Rigidbody::Update()
{
	if (!m_isOnLand)
	{
		m_velocity.y += m_gravity * MainFrame::GetInstance()->DeltaTime();
	}
	else
	{
		if (m_velocity.y > 0.0f)
		{
			m_velocity.y = 0.0f;
		}
	}
	if (!m_isNoFriction)
	{
		m_velocity.x *= 1.0f - m_friction * MainFrame::GetInstance()->DeltaTime();
		m_velocity.y *= 1.0f - m_friction * MainFrame::GetInstance()->DeltaTime();
	}
	if (abs(m_velocity.x) < 20.0f && abs(m_velocity.y) < 20.0f)
		return;

		m_gameObj->AddPosition(Vector2D({
			(float)(m_velocity.x * MainFrame::GetInstance()->DeltaTime()) ,
			(float)(m_velocity.y * MainFrame::GetInstance()->DeltaTime()) }));
}

void Rigidbody::CollisionEnter(Collider* other)
{
	int d = 20;
	if (m_gameObj->Position().y + m_box->ColSize().y <
		other->GetGameObject()->Position().y + d)
	{
		m_isOnLand = true;
		if (m_velocity.y > 0.0f)
			m_velocity.y = 0.0f;
	}
	else if (m_gameObj->Position().y >
		other->GetGameObject()->Position().y + other->ColSize().y - d)
	{
		if (m_velocity.y < 0.0f)
			m_velocity.y = 0.0f;
	}
	else if (m_gameObj->Position().x + m_box->ColSize().x >
		other->GetGameObject()->Position().x + d)
	{
		if (m_velocity.x < 0.0f)
			m_velocity.x = 0.0f;
	}
	else if (m_gameObj->Position().x <
		other->GetGameObject()->Position().x + other->ColSize().x - d)
	{
		if (m_velocity.x > 0.0f)
			m_velocity.x = 0.0f;
	}
}

void Rigidbody::CollisionExit(Collider* other)
{
	int d = 10;
	for (vector<Collider*>::iterator itr = m_box->VecCol()->begin(); itr != m_box->VecCol()->end(); itr++)
	{
		if (m_gameObj->Position().y + m_box->ColSize().y <
			(*itr)->GetGameObject()->Position().y + d)
			return;
	}
	m_isOnLand = false;
}

void Rigidbody::Collision(Collider* other)
{
	RECT r1, r2;
	long d = 1;
	r1 = { (long)m_gameObj->Position().x + d,
			(long)m_gameObj->Position().y + d,
			(long)(m_gameObj->Position().x + m_box->ColSize().x - d),
			(long)(m_gameObj->Position().y + m_box->ColSize().y - d) };
	r2 = { (long)other->GetGameObject()->Position().x,
			(long)other->GetGameObject()->Position().y,
			(long)(other->GetGameObject()->Position().x + other->ColSize().x),
			(long)(other->GetGameObject()->Position().y + other->ColSize().y) };


	SetNoIntersect(&r2, &r1);
	m_gameObj->SetPosition(Vector2D({ (float)r1.left - d, (float)r1.top - d }));


	return;
}

float Rigidbody::GetGravity()
{
	return m_gravity;
}

void Rigidbody::SetGravity(float g)
{
	m_gravity = g;
}

void Rigidbody::SetFriction(float f)
{
	m_friction = f;
}

void Rigidbody::AddForce(Vector2D vec)
{
	m_velocity.x += vec.x;
	m_velocity.y += vec.y;
}

bool Rigidbody::GetIsOnLand()
{
	return m_isOnLand;
}

Vector2D& Rigidbody::Velocity()
{
	return m_velocity;
}

void Rigidbody::SetNoFriction(bool nf)
{
	m_isNoFriction = nf;
}
