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
	anim = AnimationManager::LoadAnimation("tmp", 0.05f);
	land = AnimationManager::LoadAnimation("tmp_land", 1000);
}

void GameScene::Release()
{
	AnimationManager::ReleaseAnimation(anim);
	AnimationManager::ReleaseAnimation(land);
}

void GameScene::Start()
{
	obj1 = new GameObject();
	obj1->SetTag("land");
	obj1->Position() = { 250,150 };
	obj1->Size() = { 100, 100 };
	obj1->AddComponent(new BitmapRender(*land.bitmaps.begin()));
	obj1->AddComponent(new AnimationRender(land));
	obj1->AddComponent(new BoxCollider());
	obj1->InitializeSet();

	obj2 = new GameObject();
	obj2->SetTag("land");
	obj2->Position() = { 300,150 };
	obj2->Size() = { 100, 100 };
	obj2->AddComponent(new BitmapRender(*land.bitmaps.begin()));
	obj2->AddComponent(new AnimationRender(land));
	obj2->AddComponent(new BoxCollider());
	obj2->InitializeSet();

	obj3 = new GameObject();
	obj3->SetTag("land");
	obj3->Position() = { 100,300 };
	obj3->Size() = { 1000, 100 };
	obj3->AddComponent(new BitmapRender(*land.bitmaps.begin()));
	obj3->AddComponent(new AnimationRender(land));
	obj3->AddComponent(new BoxCollider());
	obj3->InitializeSet();
	
	obj1->SetOrderInLayer(1);
	obj2->SetOrderInLayer(2);
	obj3->SetOrderInLayer(3);
}

void GameScene::LBtnDown()
{
	GameObject* player = nullptr;
	player = new GameObject();
	player->SetTag("player");
	player->Position() = { 300,50 };
	player->Size() = { 50, 50 };

	player->AddComponent(new BitmapRender(NULL));
	player->AddComponent(new AnimationRender(anim));
	player->AddComponent(new BoxCollider());
	player->AddComponent(new Rigidbody());
	player->AddComponent(new Player());
	player->InitializeSet();

	player->SetOrderInLayer(5);
}

void GameScene::RBtnDown()
{
	obj1->Angle() += 15;
	obj2->Angle() += 15;
	obj3->Angle() += 15;

}

void GameScene::LBtnUp()
{
}

void GameScene::RBtnUp()
{
}
