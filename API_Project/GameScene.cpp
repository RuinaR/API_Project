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
void GameScene::Init()
{
	land = AnimationManager::LoadHBitmap("Bitmaps\\tmp_land\\land");
}

void GameScene::Release()
{
	AnimationManager::ReleaseHBitmap(land);
}

void GameScene::Start()
{
	GameObject* obj1, *obj2, *obj3, *obj4, *obj5;
	obj1 = new GameObject();
	obj1->SetTag("land");
	obj1->SetPosition(Vector2D({ 350,250 }));
	obj1->Size() = { 100, 100 };
	obj1->AddComponent(new BitmapRender(land));
	obj1->AddComponent(new BoxCollider());
	obj1->InitializeSet();

	obj2 = new GameObject();
	obj2->SetTag("land");
	obj2->SetPosition(Vector2D({ 400,250 }));
	obj2->Size() = { 100, 100 };
	obj2->AddComponent(new BitmapRender(land));
	obj2->AddComponent(new BoxCollider());
	obj2->InitializeSet();

	obj3 = new GameObject();
	obj3->SetTag("land");
	obj3->SetPosition(Vector2D({ 200,400 }));
	obj3->Size() = { 3000, 300 };
	obj3->AddComponent(new BitmapRender(land));
	obj3->AddComponent(new BoxCollider());
	obj3->InitializeSet();

	obj4 = new GameObject();
	obj4->SetTag("land");
	obj4->SetPosition(Vector2D({ 200,100 }));
	obj4->Size() = { 100, 600 };
	obj4->AddComponent(new BitmapRender(land));
	obj4->AddComponent(new BoxCollider());
	obj4->InitializeSet();

	obj5 = new GameObject();
	obj5->SetTag("land");
	obj5->SetPosition(Vector2D({1650,100 }));
	obj5->Size() = { 100, 600 };
	obj5->AddComponent(new BitmapRender(land));
	obj5->AddComponent(new BoxCollider());
	obj5->InitializeSet();
	
	player = nullptr;
	player = new GameObject();
	player->SetTag("player");
	player->SetPosition(Vector2D({ 300,50 }));
	player->Size() = { 50, 50 };
	player->AddComponent(new Player());
	player->InitializeSet();

	player->SetOrderInLayer(10);

	obj1->SetOrderInLayer(1);
	obj2->SetOrderInLayer(2);
	obj3->SetOrderInLayer(3);
	obj4->SetOrderInLayer(4);
	obj5->SetOrderInLayer(5);
}

void GameScene::LBtnDown()
{
	
}

void GameScene::RBtnDown()
{
	player->Angle() += 15;
}

void GameScene::LBtnUp()
{
}

void GameScene::RBtnUp()
{
}
