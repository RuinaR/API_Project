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
	bigland = AnimationManager::LoadHBitmap("Bitmaps\\obj\\bigland");
	bg = AnimationManager::LoadHBitmap("Bitmaps\\obj\\BG");
	swordObj = AnimationManager::LoadHBitmap("Bitmaps\\obj\\swordObj");
	defaultObj = AnimationManager::LoadHBitmap("Bitmaps\\obj\\defaultObj");
}

void GameScene::Release()
{
	AnimationManager::ReleaseHBitmap(bigland);
	AnimationManager::ReleaseHBitmap(land);
	AnimationManager::ReleaseHBitmap(bg);
	AnimationManager::ReleaseHBitmap(swordObj);
	AnimationManager::ReleaseHBitmap(defaultObj);
}

void GameScene::Start()
{
	WindowFrame::GetInstance()->GetBuffer()->SetBG(bg);

	obj1 = new GameObject();
	obj1->SetTag(TAG_LAND);
	obj1->SetPosition({ 500,300 });
	obj1->Size() = { 300, 100 };
	obj1->AddComponent(new BitmapRender(land));
	obj1->AddComponent(new BoxCollider());
	obj1->InitializeSet();

	obj2 = new GameObject();
	obj2->SetTag(TAG_LAND);
	obj2->SetPosition({ 1100,200 });
	obj2->Size() = { 300, 100 };
	obj2->AddComponent(new BitmapRender(land));
	obj2->AddComponent(new BoxCollider());
	obj2->InitializeSet();

	obj3 = new GameObject();
	obj3->SetTag(TAG_LAND);
	obj3->SetPosition({ 200,400 });
	obj3->Size() = { 3000, 300 };
	obj3->AddComponent(new BitmapRender(bigland));
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
	player->SetPosition({ 300,-200 });
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
	test_sword->AddComponent(new BitmapRender(swordObj));
	test_sword->SetPosition({ 700,250 });
	test_sword->InitializeSet();
	test_sword->SetOrderInLayer(6);
	test_sword->SetTag(TAG_MONSTER);

	GameObject* test_sword2 = new GameObject();
	test_sword2->AddComponent(new ChangeObject(PlayerMode::mStone, playerC));
	test_sword2->AddComponent(new BitmapRender(swordObj));
	test_sword2->SetPosition({ 700,200 });
	test_sword2->InitializeSet();
	test_sword2->SetOrderInLayer(6);
	test_sword2->SetTag(TAG_MONSTER);

	GameObject* test_stone = new GameObject();
	test_stone->AddComponent(new ChangeObject(PlayerMode::mStone, playerC));
	test_stone->AddComponent(new BitmapRender(swordObj));
	test_stone->SetPosition({ 1000,350 });
	test_stone->InitializeSet();
	test_stone->SetOrderInLayer(6);
	test_stone->SetTag(TAG_MONSTER);

	GameObject* test_stone2 = new GameObject();
	test_stone2->AddComponent(new ChangeObject(PlayerMode::mStone, playerC));
	test_stone2->AddComponent(new BitmapRender(swordObj));
	test_stone2->SetPosition({ 1200,350 });
	test_stone2->InitializeSet();
	test_stone2->SetOrderInLayer(6);
	test_stone2->SetTag(TAG_MONSTER);

	GameObject* test_default = new GameObject();
	test_default->AddComponent(new ChangeObject(PlayerMode::mDefault, playerC));
	test_default->AddComponent(new BitmapRender(defaultObj));
	test_default->SetPosition({ 1600,350 });
	test_default->InitializeSet();
	test_default->SetOrderInLayer(6);
	test_default->SetTag(TAG_MONSTER);

	GameObject* test_default2 = new GameObject();
	test_default2->AddComponent(new ChangeObject(PlayerMode::mDefault, playerC));
	test_default2->AddComponent(new BitmapRender(defaultObj));
	test_default2->SetPosition({ 1600,300 });
	test_default2->InitializeSet();
	test_default2->SetOrderInLayer(6);
	test_default2->SetTag(TAG_MONSTER);

	player->AddChild(tmp1);
	tmp1->AddChild(tmp2);
	tmp2->AddChild(tmp3);
	tmp1->SetActive(false);
	tmp2->SetActive(false);
	tmp3->SetActive(false);


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
