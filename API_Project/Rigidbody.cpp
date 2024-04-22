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
			}
			else if (rcInter.bottom == pHold->bottom)
			{
				pRect->top += nH;
				pRect->bottom += nH;
			}
		}
		else
		{
			if (rcInter.left == pHold->left)
			{
				pRect->left -= nW;
				pRect->right -= nW;
			}
			else if (rcInter.right == pHold->right)
			{
				pRect->left += nW;
				pRect->right += nW;
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
	if (m_gameObj->Position().y + m_box->ColSize().y + m_box->ColOffset().y <
		other->GetGameObject()->Position().y + other->ColOffset().y + d)
	{
		m_isOnLand = true;
	}
}

void Rigidbody::CollisionExit(Collider* other)
{
	int d = 10;
	for (set<Collider*>::iterator itr = m_box->SetCol()->begin(); itr != m_box->SetCol()->end(); itr++)
	{
		if (m_gameObj->Position().y + m_box->ColSize().y <
			(*itr)->GetGameObject()->Position().y + d)
			return;
	}
	m_isOnLand = false;
}

void Rigidbody::Collision(Collider* other)
{
	if (m_box->GetTrigger() || other->GetTrigger())
		return;

	RECT r1, r2;
	long d = 1;
	r1 = { (long)m_box->ColOffset().x + (long)m_gameObj->Position().x + d,
			(long)m_box->ColOffset().y + (long)m_gameObj->Position().y + d,
			(long)m_box->ColOffset().x + (long)(m_gameObj->Position().x + m_box->ColSize().x - d),
			(long)m_box->ColOffset().y + (long)(m_gameObj->Position().y + m_box->ColSize().y - d) };
	r2 = { (long)other->ColOffset().x + (long)other->GetGameObject()->Position().x,
			(long)other->ColOffset().y + (long)other->GetGameObject()->Position().y,
			(long)other->ColOffset().x + (long)(other->GetGameObject()->Position().x + other->ColSize().x),
			(long)other->ColOffset().y + (long)(other->GetGameObject()->Position().y + other->ColSize().y) };

	SetNoIntersect(&r2, &r1);
	m_gameObj->SetPosition(Vector2D({ (float)r1.left - d - m_box->ColOffset().x, (float)r1.top + d - m_box->ColOffset().y }));

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
