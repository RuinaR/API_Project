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
#include "RestartButton.h"

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

	m_sMaker->SetMap("testMap");

	m_sMaker->StageStart();


	GameObject* btnObj = new GameObject();
	RestartButton* btn = new RestartButton();
	btnObj->AddComponent(btn);
	btnObj->SetOrderInLayer(10);
	btnObj->InitializeSet();
	btn->SetUIPos({ 0,400 });
	btn->SetUISize({ 200,50 });
	btn->SetText(TEXT("재시작 버튼"));
	btn->SetTextColor(RGB(255, 0, 255));
	btn->SetDefaultColor(RGB(255, 255, 255));
	btn->SetHoverColor(RGB(200, 200, 200));
	btn->SetDownColor(RGB(150, 150, 150));
	btn->SetTextSize(30);
}

