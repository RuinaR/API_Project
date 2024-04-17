#include "pch.h"
#include "Player.h"
#include "GameObject.h"
#include "Component.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Rigidbody.h"

float Lerp(float start, float end, float t)
{
	return start + ((end - start) * t);
}

void Player::UpdateAnim(bool isOneTime)
{
	m_ar->SetOneTime(isOneTime);
	m_ar->ChangeAnim(m_arrAnim[(int)m_mode][(int)m_arrow][(int)m_state]);
}

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

Player::Player() : Component(), m_mode(PlayerMode::mDefault), m_arrow(PlayerArrow::right), m_state(PlayerAState::idle)
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
	RECT rect;
	GetClientRect(WindowFrame::GetInstance()->GetHWND(), &rect);
	Camera::GetInstance()->SetPos(m_gameObj->Position().x - rect.right / 2 + m_gameObj->Size().x / 2, 
													m_gameObj->Position().y - rect.right / 2 + m_gameObj->Size().y / 2);
	if (m_rig)
		m_rig->SetNoFriction(true);
}

void Player::Update()
{
	if (!m_rig)	return;
	if (!m_ar)	return;
	float speed = 250.0f;
	float curXSpeed = 0.0f;
	Vector2D playerPos = m_gameObj->Position();  // 플레이어 위치
	Vector2D camPos = Camera::GetInstance()->GetPos();  // 현재 카메라 위치
	RECT rect;
	GetClientRect(WindowFrame::GetInstance()->GetHWND(), &rect);

	// 선형 보간을 사용하여 카메라 위치 업데이트
	float smoothFactor = 0.02f;  // 부드러운 이동을 위한 보간 계수
	Vector2D newCamPos = {
		Lerp(camPos.x, playerPos.x - rect.right / 2 + m_gameObj->Size().x / 2, smoothFactor),
		Lerp(camPos.y, playerPos.y - rect.bottom / 2 + m_gameObj->Size().y/2, smoothFactor)
	};
	Camera::GetInstance()->SetPos(newCamPos.x, newCamPos.y);

	//우측 이동
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!m_rig->GetIsOnLand())
			return;
		curXSpeed = speed;
		m_rig->Velocity() = {speed, 0.0f};
		m_arrow = PlayerArrow::right;
		if (m_state != PlayerAState::walk)
		{
			m_state = PlayerAState::walk;
			UpdateAnim(false);
		}
	}//좌측 이동
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (!m_rig->GetIsOnLand())
			return;
		curXSpeed = -speed;
		m_rig->Velocity() = { -speed, 0.0f };
		m_arrow = PlayerArrow::left;
		if (m_state != PlayerAState::walk)
		{
			m_state = PlayerAState::walk;
			UpdateAnim(false);
		}
	}//Idle상태
	else if (m_rig->GetIsOnLand()) //조건 추가?
	{
		m_rig->Velocity() = { 0.0f, 0.0f };
		if (m_state != PlayerAState::idle)
		{
			m_state = PlayerAState::idle;
			UpdateAnim(false);
		}
	}

	//점프
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (m_rig->GetIsOnLand() &&
			m_rig->Velocity().y >= -0.1f &&
			m_rig->Velocity().y <= 0.1f)
		{
			static bool isJump = false;
			if (!isJump)
			{
				m_rig->Velocity() = {curXSpeed, -500.0f};
				if (m_state != PlayerAState::jump)
				{
					m_state = PlayerAState::jump;
					UpdateAnim(true);
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
