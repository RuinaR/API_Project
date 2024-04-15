#include "pch.h"
#include "Player.h"
#include "GameObject.h"
#include "Component.h"
#include "Collider.h"
#include "BoxCollider.h"
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
	m_mode = PlayerMode::mDefault;
	string modeStr[(int)PlayerMode::max] = { "default" };
	string arrowStr[(int)PlayerArrow::max] = { "left", "right" };
	string stateStr[(int)PlayerAState::max] = {};
	stateStr[(int)PlayerAState::idle] = "idle";
	stateStr[(int)PlayerAState::walk] = "walk";
	stateStr[(int)PlayerAState::jump] = "jump";

	for (int a = 0; a < (int)PlayerMode::max; a++)
	{
		for (int i = 0; i < (int)PlayerArrow::max; i++)
		{
			for (int j = 0; j < (int)PlayerAState::max; j++)
			{
				string path = "Bitmaps\\Player\\" + modeStr[a] + "\\" + arrowStr[i] + "\\" + stateStr[j];
				float atime = 0.1f;
				if (j == (int)PlayerAState::jump) atime = 0.07f;
				m_arrAnim[a][i][j] = AnimationManager::LoadAnimation(path, atime);
			}
		}
	}
	m_ar = new AnimationRender(m_arrAnim[(int)PlayerMode::mDefault][(int)PlayerArrow::right][(int)PlayerAState::idle]);
	m_rig = new Rigidbody();
	m_gameObj->AddComponent(new BoxCollider());
	m_gameObj->AddComponent(new BitmapRender(m_arrAnim[(int)PlayerMode::mDefault][(int)PlayerArrow::right][(int)PlayerAState::idle].bitmaps[0]));
	m_gameObj->AddComponent(m_ar);
	m_gameObj->AddComponent(m_rig);
}

void Player::Release()
{

	for (int a = 0; a < (int)PlayerMode::max; a++)
	{
		for (int i = 0; i < (int)PlayerArrow::max; i++)
		{
			for (int j = 0; j < (int)PlayerAState::max; j++)
			{
				AnimationManager::ReleaseAnimation(m_arrAnim[a][i][j]);
			}
		}
	}
}

void Player::Start()
{
}

void Player::Update()
{
	if (!m_rig)
		return;

	WindowFrame::GetInstance()->GetBuffer()->CameraPos() =
	{ m_gameObj->Position().x,
	m_gameObj->Position().y};

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (!m_rig->GetIsOnLand())
			return;
		m_rig->AddForce(Vector2D({ -250.f * MainFrame::GetInstance()->DeltaTime(), 0.0f}));
		//m_gameObj->Position().x -= 150 * MainFrame::GetInstance()->DeltaTime();
		m_arrow = PlayerArrow::left;
		if (m_ar->GetCurrentAnim().identity != m_arrAnim[(int)m_mode][(int)PlayerArrow::left][(int)PlayerAState::walk].identity)
		{
			m_ar->ChangeAnim(m_arrAnim[(int)m_mode][(int)m_arrow][(int)PlayerAState::walk]);
			m_ar->SetOneTime(false);
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!m_rig->GetIsOnLand())
			return;
		m_rig->AddForce(Vector2D({ 250.f * MainFrame::GetInstance()->DeltaTime(), 0.0f }));
		//m_gameObj->Position().x += 150 * MainFrame::GetInstance()->DeltaTime();

		m_arrow = PlayerArrow::right;
		if (m_ar->GetCurrentAnim().identity != m_arrAnim[(int)m_mode][(int)PlayerArrow::right][(int)PlayerAState::walk].identity)
		{
			m_ar->ChangeAnim(m_arrAnim[(int)m_mode][(int)m_arrow][(int)PlayerAState::walk]);
			m_ar->SetOneTime(false);
		}
	}
	else
	{
		if (!m_rig->GetIsOnLand())
			return;
		if (m_ar->GetCurrentAnim().identity != m_arrAnim[(int)m_mode][(int)m_arrow][(int)PlayerAState::idle].identity)
		{
			m_ar->ChangeAnim(m_arrAnim[(int)m_mode][(int)m_arrow][(int)PlayerAState::idle]);
			m_ar->SetOneTime(false);
		}
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
				m_rig->AddForce(Vector2D({ 0.0f, -500.f }));
				if (m_ar->GetCurrentAnim().identity != m_arrAnim[(int)m_mode][(int)m_arrow][(int)PlayerAState::jump].identity)
				{
					m_ar->SetOneTime(true);
					m_ar->ChangeAnim(m_arrAnim[(int)m_mode][(int)m_arrow][(int)PlayerAState::jump]);
				}
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
