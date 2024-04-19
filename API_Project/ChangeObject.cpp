#include "pch.h"
#include "ChangeObject.h"
#include "BoxCollider.h"


ChangeObject::ChangeObject(PlayerMode mode, Player* player)
	:m_mode(mode), m_player(player), Component()
{
}

ChangeObject::~ChangeObject()
{
}

void ChangeObject::Initialize()
{
	m_gameObj->Size() = { 50,50 };
	m_bit = AnimationManager::LoadHBitmap("Bitmaps\\obj\\change");
	m_gameObj->AddComponent(new BitmapRender(m_bit));
	m_gameObj->AddComponent(new BoxCollider());
	m_gameObj->SetTag(TAG_CHANGE);
}

void ChangeObject::Release()
{
	AnimationManager::ReleaseHBitmap(m_bit);
}

void ChangeObject::Start()
{
}

void ChangeObject::Update()
{
	
	if (m_player->GetState() == PlayerAState::eating)
	{
		if (m_gameObj->Position().y < m_player->GetGameObject()->Position().y + 10 &&
			m_gameObj->Position().y > m_player->GetGameObject()->Position().y - 10)
		{
			if (m_player->GetArrow() == PlayerArrow::left &&
				m_gameObj->Position().x < m_player->GetGameObject()->Position().x &&
				m_gameObj->Position().x > m_player->GetGameObject()->Position().x - m_area)
			{
				m_gameObj->AddPosition({ m_speed * MainFrame::GetInstance()->DeltaTime(), 0.0f });
			}
			else if (m_player->GetArrow() == PlayerArrow::right &&
				m_gameObj->Position().x > m_player->GetGameObject()->Position().x &&
				m_gameObj->Position().x < m_player->GetGameObject()->Position().x + m_area)
			{
				m_gameObj->AddPosition({ -m_speed * MainFrame::GetInstance()->DeltaTime(), 0.0f });
			}
		}
	}
}

PlayerMode ChangeObject::GetMode()
{
	return m_mode;
}
