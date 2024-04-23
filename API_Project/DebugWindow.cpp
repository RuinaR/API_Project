#include "pch.h"
#include "DebugWindow.h"

DebugWindow* DebugWindow::m_Pthis = nullptr;

void DebugWindow::Initialize()
{

}

void DebugWindow::Release()
{

}

void DebugWindow::Start()
{
}

void DebugWindow::Update()
{
	RECT rect = { 
        m_gameObj->Position().x,
        m_gameObj->Position().y,
		m_gameObj->Position().x + m_gameObj->Size().x,
        m_gameObj->Position().y + m_gameObj->Size().y };
    FillRectWithColor(WindowFrame::GetInstance()->GetBuffer()->GetHDC(), rect, RGB(255, 255, 0));
	DrawTextInRect(WindowFrame::GetInstance()->GetBuffer()->GetHDC(), 
		ConvertToWideString(
			m_text + "\n\n\n" + "---COUNT---\n" + 
			"object : " + to_string(ObjectManager::GetInstance()->Count()) + "\n"
			"collider : " + to_string(CollisionManager::GetInstance()->Count())
		), rect);
}

DebugWindow* DebugWindow::GetInstance()
{
    return m_Pthis;
}

void DebugWindow::SetText(string text)
{
	m_text = text;
}

void DebugWindow::Create()
{
	if (m_Pthis == nullptr)
	{
		m_Pthis = new DebugWindow();
		GameObject* DW = new GameObject();
		DW->AddComponent(m_Pthis);
		DW->SetPosition({ 0,0 });
		DW->Size() = { 200,200 };
		DW->SetOrderInLayer(10);
		DW->SetTag("DebugWindow");
		DW->InitializeSet();
	}
}


void DebugWindow::Destroy()
{
	if (m_Pthis != nullptr)
	{
		if (m_Pthis->m_gameObj != nullptr)
		{
			m_Pthis->m_gameObj->SetDestroy(true);
		}
		else
		{
			delete m_Pthis;
		}
		m_Pthis = nullptr;
	}
}

