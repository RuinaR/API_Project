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
	if (m_arrAnim[(int)m_mode][(int)m_arrow][(int)m_state].identity != m_ar->GetCurrentAnim().identity)
	{
		m_ar->ChangeAnim(m_arrAnim[(int)m_mode][(int)m_arrow][(int)m_state]);
	}
}

void Player::FlyAction()
{
	if (!m_rig->GetIsOnLand())
	{
		if (GetAsyncKeyState(m_atkKey)) //떨어지기
		{
			m_state = PlayerAState::idle;
			m_rig->Velocity().y = 0.0f;
			UpdateAnim(false);
			return;
		}
		if (GetAsyncKeyState(m_jumpKey)) //위로 가속
		{
			m_flyTimer.tick();
			if (m_flyTimer.getTotalDeltaTime() > 0.2)
			{
				m_rig->Velocity().y = -m_speed_fly;
				m_flyTimer.resetTotalDeltaTime();
			}
		}
		if (GetAsyncKeyState(m_rightKey))//우측 fly 이동
		{
			m_rig->Velocity() = { m_speed, m_rig->Velocity().y };
			m_arrow = PlayerArrow::right;
		}
		else if (GetAsyncKeyState(m_leftKey))//좌측 fly 이동
		{
			m_rig->Velocity() = { -m_speed, m_rig->Velocity().y };
			m_arrow = PlayerArrow::left;
		}
		else //fly idle
		{
			m_rig->Velocity() = { 0.0f, m_rig->Velocity().y };
		}
	}
	else
	{
		m_state = PlayerAState::idle;
		m_rig->Velocity() = { 0.0f, 0.0f };
	}
	UpdateAnim(false);
}

void Player::MoveLeft()
{
	if (m_rig->GetIsOnLand())
	{
		m_arrow = PlayerArrow::left;
		UpdateAnim(false);
		if (GetAsyncKeyState(m_runKey)) //Run_Left
		{
			m_curXSpeed = -m_speed_run;
			m_state = PlayerAState::run;
			UpdateAnim(false);
		}
		else //Walk_Left
		{
			m_curXSpeed = -m_speed;
			m_state = PlayerAState::walk;
			UpdateAnim(false);
		}
		m_rig->Velocity() = { m_curXSpeed, 0.0f };
	}
}

void Player::MoveRight()
{
	if (m_rig->GetIsOnLand())
	{
		m_arrow = PlayerArrow::right;
		UpdateAnim(false);
		if (GetAsyncKeyState(m_runKey)) //Run_Right
		{
			m_curXSpeed = m_speed_run;
			m_state = PlayerAState::run;
			UpdateAnim(false);
		}
		else //Walk_Right
		{
			m_curXSpeed = m_speed;
			m_state = PlayerAState::walk;
			UpdateAnim(false);
		}
		m_rig->Velocity() = { m_curXSpeed, 0.0f };
	}
}

void Player::JumpAction()
{
	m_flyTimer.tick();
	//점프
	if (m_rig->GetIsOnLand() &&
		m_rig->Velocity().y >= -0.1f &&
		m_rig->Velocity().y <= 0.1f)
	{
		static bool _isJump = false;
		if (!_isJump)
		{
			m_rig->Velocity() = { m_curXSpeed, -500.0f };
			m_state = PlayerAState::jump;
			UpdateAnim(true);
			cout << "Jump" << endl;
			_isJump = true;
			m_flyTimer.resetTotalDeltaTime();
			m_flyTimer.tick();
		}
		else
		{
			_isJump = false;
		}
	}
	else if (m_flyTimer.getTotalDeltaTime() > 0.2f)//날기 start
	{
		m_flyTimer.tick();
		m_flyTimer.resetTotalDeltaTime();
		m_state = PlayerAState::fly;
		m_rig->Velocity().y = -m_speed_fly;
		m_rig->SetGravity(150);
		UpdateAnim(false);
	}
}

void Player::Idle()
{
	m_rig->Velocity() = { 0.0f, 0.0f };
	m_curXSpeed = 0.0f;
	m_state = PlayerAState::idle;
	UpdateAnim(false);
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

Player::Player()
	: Component(), m_mode(PlayerMode::mDefault), m_arrow(PlayerArrow::right), m_state(PlayerAState::idle)
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
	stateStr[(int)PlayerAState::run] = "run";
	stateStr[(int)PlayerAState::fly] = "fly";

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

	m_leftKey = VK_LEFT;
	m_rightKey = VK_RIGHT;
	m_runKey = VK_SHIFT;
	m_jumpKey = VK_SPACE;
	m_atkKey = 0x5A;	//Z키
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

	m_flyTimer.tick();
}

void Player::Update()
{
	if (!m_rig)	return;
	if (!m_ar)	return;

	Vector2D playerPos = m_gameObj->Position();  // 플레이어 위치
	Vector2D camPos = Camera::GetInstance()->GetPos();  // 현재 카메라 위치
	RECT rect;
	GetClientRect(WindowFrame::GetInstance()->GetHWND(), &rect);
	if (m_state != PlayerAState::fly)m_rig->SetGravity(1200);
	// 선형 보간을 사용하여 카메라 위치 업데이트
	float smoothFactor = 0.02f;  // 부드러운 이동을 위한 보간 계수
	Vector2D newCamPos = {
		Lerp(camPos.x, playerPos.x - rect.right / 2 + m_gameObj->Size().x / 2, smoothFactor),
		Lerp(camPos.y, playerPos.y - rect.bottom / 2 + m_gameObj->Size().y / 2, smoothFactor)
	};
	Camera::GetInstance()->SetPos(newCamPos.x, newCamPos.y);

	if (m_state == PlayerAState::fly) //나는 중일때의 처리
	{
		FlyAction();
		return;
	}
	if (GetAsyncKeyState(m_rightKey))//우측 이동
	{
		MoveRight();
	}	
	if (GetAsyncKeyState(m_leftKey))//좌측 이동
	{
		MoveLeft();
	}
	if (m_rig->GetIsOnLand() && !GetAsyncKeyState(m_leftKey) && !GetAsyncKeyState(m_rightKey)) 	//Idle
	{
		Idle();
	}
	if (GetAsyncKeyState(m_jumpKey)) //점프 & 날기
	{
		JumpAction();
	}
}
