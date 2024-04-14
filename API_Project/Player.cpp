#include "pch.h"
#include "Player.h"
#include "GameObject.h"
#include "Component.h"
#include "Collider.h"
#include "Rigidbody.h"
void Player::CollisionEnter(Collider* other)
{
	cout << "P_Enter" << endl;
}

void Player::CollisionExit(Collider* other)
{
	cout << "P_Exit" << endl;
}

void Player::Collision(Collider* other)
{

}

Player::Player() : Component()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
}

void Player::Release()
{
}

void Player::Start()
{
	m_rig = m_gameObj->GetComponent<Rigidbody>();
}

void Player::Update()
{
	if (!m_rig)
		return;

	if (GetAsyncKeyState(VK_LEFT))
	{
		//if (m_rig->GetIsOnLand())
		m_rig->AddForce(Vector2D({ -10.0f, 0.0f }));
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		//if (m_rig->GetIsOnLand())
		m_rig->AddForce(Vector2D({ 10.0f, 0.0f }));
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (m_rig->GetIsOnLand() && 
			m_rig->GetVelocity().y >= -0.1f && 
			m_rig->GetVelocity().y <= 0.1f)
		{
			static bool isJump = false;
			if (!isJump)
			{
				m_rig->AddForce(Vector2D({ 0.0f, -800.0f }));
				cout << "Jump" << endl;
				isJump = true;
			}
			else
			{
				isJump = false;
			}
		}
	}
}
