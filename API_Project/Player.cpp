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
		if (GetAsyncKeyState(m_atkKey)) //��������
		{
			m_state = PlayerAState::idle;
			m_rig->Velocity().y = 0.0f;
			UpdateAnim(false);
			return;
		}
		if (GetAsyncKeyState(m_jumpKey)) //���� ����
		{
			m_flyTimer.tick();
			if (m_flyTimer.getTotalDeltaTime() > m_dblTime)
			{
				m_rig->Velocity().y = -m_speed_fly;
				m_flyTimer.resetTotalDeltaTime();
			}
		}
		if (GetAsyncKeyState(m_rightKey))//���� fly �̵�
		{
			m_rig->Velocity() = { m_speed / 2, m_rig->Velocity().y };
			m_arrow = PlayerArrow::right;
		}
		else if (GetAsyncKeyState(m_leftKey))//���� fly �̵�
		{
			m_rig->Velocity() = { -m_speed / 2, m_rig->Velocity().y };
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
		if ((m_leftKeyTimer.getDeltaTime() <= m_dblTime &&
			(m_state == PlayerAState::walk ||
				m_state == PlayerAState::jump ||
				m_state == PlayerAState::idle)) ||
			m_state == PlayerAState::run)  //Run_Left
		{
			m_curXSpeed = -m_speed_run;
			m_state = PlayerAState::run;
			UpdateAnim(false);
		}
		else if (m_state == PlayerAState::eat_idle ||
			m_state == PlayerAState::eat_jump ||
			m_state == PlayerAState::eat_move)//eat_move_left
		{
			m_curXSpeed = -m_eatSpeed;
			m_state = PlayerAState::eat_move;
			UpdateAnim(false);
		}
		else if (m_state == PlayerAState::idle || 
			m_state == PlayerAState::walk || 
			m_state == PlayerAState::jump)//Walk_Left
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
		if ((m_rightKeyTimer.getDeltaTime() <= m_dblTime &&
				(m_state == PlayerAState::walk || 
				m_state == PlayerAState::jump || 
				m_state == PlayerAState::idle )) ||
			m_state == PlayerAState::run)  //Run_Right
		{
			m_curXSpeed = m_speed_run;
			m_state = PlayerAState::run;
			UpdateAnim(false);
		}
		else if (m_state == PlayerAState::eat_idle ||
			m_state == PlayerAState::eat_jump ||
			m_state == PlayerAState::eat_move)//eat_move_right
		{
			m_curXSpeed = m_eatSpeed;
			m_state = PlayerAState::eat_move;
			UpdateAnim(false);
		}
		else if (m_state == PlayerAState::idle || 
			m_state == PlayerAState::walk || 
			m_state == PlayerAState::jump)//Walk_Right
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
	//����
	if (m_rig->GetIsOnLand() &&
		m_rig->Velocity().y >= -0.1f &&
		m_rig->Velocity().y <= 0.1f)
	{
		if (m_state == PlayerAState::eat_idle ||
			m_state == PlayerAState::eat_move ||
			m_state == PlayerAState::eat_jump)
		{
			m_rig->Velocity() = { m_curXSpeed, -m_JumpV / 2 };
			m_state = PlayerAState::eat_jump;
		}
		else
		{
			m_rig->Velocity() = { m_curXSpeed, -m_JumpV };
			m_state = PlayerAState::jump;
		}
		UpdateAnim(true);
		cout << "Jump" << endl;
	}
	else if (m_flyTimer.getDeltaTime() > m_dblTime &&
		m_state != PlayerAState::eat_jump &&
		m_state != PlayerAState::eat_idle &&
		m_state != PlayerAState::eat_move)//���� start
	{
		m_state = PlayerAState::fly;
		m_rig->Velocity().y = -m_speed_fly;
		m_rig->SetGravity(m_flyGravity);
		UpdateAnim(false);
		cout << "Fly" << endl;
	}
}

void Player::Idle()
{
	if (m_state == PlayerAState::eat_idle ||
		m_state == PlayerAState::eat_move ||
		m_state == PlayerAState::eat_jump)
	{
		m_state = PlayerAState::eat_idle;
	}
	else
	{
		m_state = PlayerAState::idle;
	}
	m_rig->Velocity() = { 0.0f, 0.0f };
	m_curXSpeed = 0.0f;
	UpdateAnim(false);
}

void Player::CollisionEnter(Collider* other)
{
	cout << "Player_CollisionEnter : Target : " << other->GetGameObject()->GetTag() << endl;
}

void Player::CollisionExit(Collider* other)
{
	cout << "Player_CollisionExit : Target : " << other->GetGameObject()->GetTag() << endl;
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
	stateStr[(int)PlayerAState::eat_idle] = "eat_idle";
	stateStr[(int)PlayerAState::eat_move] = "eat_move";
	stateStr[(int)PlayerAState::eat_jump] = "eat_jump";

	for (int a = 0; a < (int)PlayerMode::max; a++)
	{
		for (int i = 0; i < (int)PlayerArrow::max; i++)
		{
			for (int j = 0; j < (int)PlayerAState::max; j++)
			{
				string path = "Bitmaps\\Player\\" + modeStr[a] + "\\" + arrowStr[i] + "\\" + stateStr[j];
				float atime = 0.1f;
				if (j == (int)PlayerAState::jump) atime = 0.07f;
				else if (j == (int)PlayerAState::idle || j == (int)PlayerAState::eat_idle) atime = 0.25f;
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
	m_jumpKey = VK_SPACE;
	m_atkKey = 0x5A;	//ZŰ, ATK
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

	m_startGravity = m_rig->GetGravity();
	m_flyTimer.tick();
	m_leftKeyTimer.tick();
	m_rightKeyTimer.tick();
}

void Player::Update()
{
	if (!m_rig)	return;
	if (!m_ar)	return;

	Vector2D playerPos = m_gameObj->Position();  // �÷��̾� ��ġ
	Vector2D camPos = Camera::GetInstance()->GetPos();  // ���� ī�޶� ��ġ
	RECT rect;
	GetClientRect(WindowFrame::GetInstance()->GetHWND(), &rect);
	if (m_state != PlayerAState::fly)m_rig->SetGravity(m_startGravity);
	// ���� ������ ����Ͽ� ī�޶� ��ġ ������Ʈ
	float smoothFactor = 0.02f;  // �ε巯�� �̵��� ���� ���� ���
	Vector2D newCamPos = {
		Lerp(camPos.x, playerPos.x - rect.right / 2 + m_gameObj->Size().x / 2, smoothFactor),
		Lerp(camPos.y, playerPos.y - rect.bottom / 2 + m_gameObj->Size().y / 2, smoothFactor)
	};
	Camera::GetInstance()->SetPos(newCamPos.x, newCamPos.y);

	if (m_state == PlayerAState::fly) //���� ���϶��� ó��
	{
		FlyAction();
		return;
	}

	//eat ���� �׽�Ʈ��, ���߿� �����----
	static bool isDouble = false;
	if (!GetAsyncKeyState(VK_CONTROL))
		isDouble = true;
	if (GetAsyncKeyState(VK_CONTROL)) 
	{
		if (isDouble)
		{
			if (m_state == PlayerAState::idle)
			{
				m_state = PlayerAState::eat_idle;
				cout << "eat_idle" << endl;
			}
			else if (m_state == PlayerAState::eat_idle)
			{
				m_state = PlayerAState::idle;
				cout << "idle" << endl;
			}
			UpdateAnim(false);
			isDouble = false;
		}
	}
	//----
	if (m_rig->GetIsOnLand() && !GetAsyncKeyState(m_leftKey) && !GetAsyncKeyState(m_rightKey) && !GetAsyncKeyState(m_atkKey)) 	//Idle
		Idle();



	if (!(GetAsyncKeyState(m_rightKey) && GetAsyncKeyState(m_leftKey))) //�̵�
	{
		if (GetAsyncKeyState(m_rightKey))//���� �̵�
		{
			if (m_rightKeyTrigger)
			{
				m_rightKeyTrigger = false;
				m_rightKeyTimer.tick();
			}
			MoveRight();
		}
		else
			m_rightKeyTrigger = true;

		if (GetAsyncKeyState(m_leftKey))//���� �̵�
		{
			if (m_leftKeyTrigger)
			{
				m_leftKeyTrigger = false;
				m_leftKeyTimer.tick();
			}
			MoveLeft();
		}
		else
			m_leftKeyTrigger = true;
	}
	if (GetAsyncKeyState(m_jumpKey)) //���� & ����
	{
		if (m_jumpFlyTrigger)
		{
			m_jumpFlyTrigger = false;
			m_flyTimer.tick();
			JumpAction();
		}
	}
	else
		m_jumpFlyTrigger = true;
}
