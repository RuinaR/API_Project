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


void GameScene::Init()
{
	land = AnimationManager::LoadHBitmap("Bitmaps\\obj\\land");
}

void GameScene::Release()
{
	AnimationManager::ReleaseHBitmap(land);
}

void GameScene::Start()
{
	obj1 = new GameObject();
	obj1->SetTag(TAG_LAND);
	obj1->SetPosition({ 500,300 });
	obj1->Size() = { 300, 100 };
	obj1->AddComponent(new BitmapRender(land));
	obj1->AddComponent(new BoxCollider());
	obj1->InitializeSet();

	obj2 = new GameObject();
	obj2->SetTag(TAG_LAND);
	obj2->SetPosition({ 900,200 });
	obj2->Size() = { 300, 100 };
	obj2->AddComponent(new BitmapRender(land));
	obj2->AddComponent(new BoxCollider());
	obj2->InitializeSet();

	obj3 = new GameObject();
	obj3->SetTag(TAG_LAND);
	obj3->SetPosition({ 200,400 });
	obj3->Size() = { 3000, 300 };
	obj3->AddComponent(new BitmapRender(land));
	obj3->AddComponent(new BoxCollider());
	obj3->InitializeSet();

	obj4 = new GameObject();
	obj4->SetTag(TAG_LAND);
	obj4->SetPosition({ 200,100 });
	obj4->Size() = { 100, 600 };
	obj4->AddComponent(new BitmapRender(land));
	obj4->AddComponent(new BoxCollider());
	obj4->InitializeSet();

	obj5 = new GameObject();
	obj5->SetTag(TAG_LAND);
	obj5->SetPosition({ 1650,100 });
	obj5->Size() = { 100, 600 };
	obj5->AddComponent(new BitmapRender(land));
	obj5->AddComponent(new BoxCollider());
	obj5->InitializeSet();
	
	player = new GameObject();
	player->SetTag(TAG_PLAYER);
	player->SetPosition({ 300,200 });
	Player* playerC = new Player();
	player->AddComponent(playerC);
	player->InitializeSet();

	player->SetOrderInLayer(10);

	tmp1 = new GameObject();
	tmp1->SetPosition({ 280,190 });
	tmp1->Size() = { 20,20 };
	tmp1->AddComponent(new BitmapRender(land));
	tmp1->InitializeSet();

	tmp2 = new GameObject();
	tmp2->SetPosition({ 260, 180 });
	tmp2->Size() = { 20,20 };
	tmp2->AddComponent(new BitmapRender(land));
	tmp2->InitializeSet();

	tmp3 = new GameObject();
	tmp3->SetPosition({ 240, 170 });
	tmp3->Size() = { 20,20 };
	tmp3->AddComponent(new BitmapRender(land));
	tmp3->InitializeSet();

	GameObject* test_sword = new GameObject();
	test_sword->AddComponent(new ChangeObject(PlayerMode::mSword, playerC));
	test_sword->SetPosition({ 700,250 });
	test_sword->InitializeSet();
	test_sword->SetOrderInLayer(6);
	test_sword->SetTag(TAG_MONSTER);

	GameObject* test_sword2 = new GameObject();
	test_sword2->AddComponent(new ChangeObject(PlayerMode::mSword, playerC));
	test_sword2->SetPosition({ 1000,350 });
	test_sword2->InitializeSet();
	test_sword2->SetOrderInLayer(6);
	test_sword2->SetTag(TAG_MONSTER);

	player->AddChild(tmp1);
	tmp1->AddChild(tmp2);
	tmp2->AddChild(tmp3);

	obj1->SetOrderInLayer(1);
	obj2->SetOrderInLayer(2);
	obj3->SetOrderInLayer(3);
	obj4->SetOrderInLayer(4);
	obj5->SetOrderInLayer(5);
}

void GameScene::LBtnDown()
{
	GameScene* newScene = new GameScene();
	newScene->Init();
	WindowFrame::GetInstance()->SetScene(newScene);
}

void GameScene::RBtnDown()
{
	tmp2->SetDestroy(true);
}

void GameScene::LBtnUp()
{
}

void GameScene::RBtnUp()
{
}
