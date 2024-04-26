#include "pch.h"
#include "GameScene.h"
#include "AnimationRender.h"
#include "BitmapRender.h"
#include "Component.h"
#include "GameObject.h"
#include "BitmapRender.h"
#include "AnimationRender.h"
#include "BoxCollider.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Player.h"
#include "ChangeObject.h"
#include "StageMaker.h"
#include "ColorButton.h"
#include "DebugWindow.h"
#include "SceneChanger.h"

void GameScene::Init()
{
	if (DEBUGMODE)
		DebugWindow::Create();
}

void GameScene::Release()
{
	if (DEBUGMODE)
		DebugWindow::Destroy();
}

void GameScene::Start()
{
	GameObject* newObj = new GameObject();
	m_sMaker = new StageMaker();
	newObj->AddComponent(m_sMaker);
	newObj->InitializeSet();

	m_sMaker->SetMap(FILE_MAP);
	m_sMaker->StageStart();

	GameObject* Obj = new GameObject();
	SceneChanger* sceneChanger = new SceneChanger();
	Obj->AddComponent(sceneChanger);
	Obj->InitializeSet();

	GameObject* btnObj = new GameObject();
	ColorButton* btn = new ColorButton();
	btnObj->AddComponent(btn);
	btnObj->SetOrderInLayer(10);
	btnObj->InitializeSet();
	btn->SetUIPos({ 0,400 });
	btn->SetUISize({ 200,50 });
	btn->SetText(TEXT("GameScene Load"));
	btn->SetTextColor(RGB(255, 0, 255));
	btn->SetDefaultColor(RGB(255, 255, 255));
	btn->SetHoverColor(RGB(200, 200, 200));
	btn->SetDownColor(RGB(150, 150, 150));
	btn->SetTextSize(20);
	btn->SetEvent(bind(&SceneChanger::ChangeGameScene, sceneChanger));

	GameObject* btnObj2 = new GameObject();
	ColorButton* btn2 = new ColorButton();
	btnObj2->AddComponent(btn2);
	btnObj2->SetOrderInLayer(10);
	btnObj2->InitializeSet();
	btn2->SetUIPos({ 0,500 });
	btn2->SetUISize({ 200,50 });
	btn2->SetText(TEXT("StartScene Load"));
	btn2->SetTextColor(RGB(255, 0, 255));
	btn2->SetDefaultColor(RGB(255, 255, 255));
	btn2->SetHoverColor(RGB(200, 200, 200));
	btn2->SetDownColor(RGB(150, 150, 150));
	btn2->SetTextSize(20);
	btn2->SetEvent(bind(&SceneChanger::ChangeStartScene, sceneChanger));

}

