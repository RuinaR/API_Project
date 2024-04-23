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
#include "RestartBtn.h"
#include "DebugWindow.h"

void GameScene::Init()
{
	DebugWindow::Create();
}

void GameScene::Release()
{
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


	GameObject* btn = new GameObject();
	btn->Size() = { 200,100 };
	RestartBtn* re = new RestartBtn();
	btn->AddComponent(re);
	btn->SetOrderInLayer(10);
	btn->InitializeSet();
	re->SetUIPos({ 0,300 });

}

