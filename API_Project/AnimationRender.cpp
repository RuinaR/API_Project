#include "pch.h"
#include "AnimationRender.h"
#include "BitmapRender.h"
#include "GameObject.h"

AnimationRender::AnimationRender(Animation anim)
	:Component(), m_isPlay(true), m_updateTimer(0.0f), m_curItr()
{
	m_anim = anim;
}

void AnimationRender::Initialize()
{

}

void AnimationRender::Release()
{
	m_bitren = nullptr;
}

void AnimationRender::ChangeAnim(Animation anim)
{
	m_anim = anim;
	m_curItr = m_anim.bitmaps.begin();
}

void AnimationRender::Start()
{
	m_bitren = m_gameObj->GetComponent<BitmapRender>();
	m_curItr = m_anim.bitmaps.begin();
}

void AnimationRender::Update()
{
	if (!m_isPlay)
		return;

	m_updateTimer += MainFrame::GetInstance()->DeltaTime();
	if (m_updateTimer < (float)m_anim.time)
		return;

	if (m_isOneTime && m_curItr == --m_anim.bitmaps.end())
		return;
	m_updateTimer = 0.0f;
	m_curItr++;
	if (m_curItr == m_anim.bitmaps.end())
	{
		m_curItr = m_anim.bitmaps.begin();
	}

	m_bitren->ChangeBitmap(*m_curItr);
}

void AnimationRender::SetPlay(bool play)
{
	m_isPlay = play;
}

void AnimationRender::SetOneTime(bool b)
{
	m_isOneTime = b;
}

const Animation& AnimationRender::GetCurrentAnim()
{
	return m_anim;
}
