#include "pch.h"
#include "EditerScene.h"
#include "ColorButton.h"
#include "SceneChanger.h"
#include "DebugWindow.h"
void EditerScene::Init()
{
	SceneChanger::Create();
	DebugWindow::Create();
	DebugWindow::GetInstance()->SetDWPos({ 0,400 });
}

void EditerScene::Release()
{
	SceneChanger::Destroy();
	DebugWindow::Destroy();
}

void EditerScene::Start()
{
	GameObject* newObj = new GameObject();
	m_edit = new Edit();
	newObj->AddComponent(m_edit);
	newObj->InitializeSet();
	m_edit->SetMap(FILE_MAP);


	GameObject* btnObj = new GameObject();
	ColorButton* btn = new ColorButton();
	btnObj->AddComponent(btn);
	btnObj->SetOrderInLayer(10);
	btnObj->InitializeSet();
	btn->SetUIPos({ 0,10 });
	btn->SetUISize({ 190,50 });
	btn->SetText(TEXT("StartScene Load"));
	btn->SetTextColor(RGB(255, 0, 255));
	btn->SetDefaultColor(RGB(255, 255, 255));
	btn->SetHoverColor(RGB(200, 200, 200));
	btn->SetDownColor(RGB(150, 150, 150));
	btn->SetTextSize(20);
	btn->SetEvent(bind(&SceneChanger::ChangeStartScene, SceneChanger::GetInstance()));
}
