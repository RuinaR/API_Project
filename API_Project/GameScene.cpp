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


void GameScene::Init()
{

}

void GameScene::Release()
{
}

void GameScene::Start()
{
	GameObject* newObj = new GameObject();
	m_sMaker = new StageMaker();
	newObj->AddComponent(m_sMaker);
	newObj->InitializeSet();

	m_sMaker->SetMap("testMap");
}

void GameScene::LBtnDown()
{
	m_sMaker->StageStart();
}

void GameScene::RBtnDown()
{
	GameScene* newScene = new GameScene();
	newScene->Init();
	WindowFrame::GetInstance()->SetScene(newScene);
}

void GameScene::LBtnUp()
{
}

void GameScene::RBtnUp()
{
}
