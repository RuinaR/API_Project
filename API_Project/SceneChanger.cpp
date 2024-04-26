#include "pch.h"
#include "SceneChanger.h"
#include "Scene.h"
#include "GameScene.h"
#include "StartScene.h"
#include "EditerScene.h"
void SceneChanger::Initialize()
{
}

void SceneChanger::Release()
{
}

void SceneChanger::Start()
{
}

void SceneChanger::Update()
{
}

void SceneChanger::ChangeGameScene()
{
	WindowFrame::GetInstance()->SetScene(new GameScene());
}

void SceneChanger::ChangeStartScene()
{
	WindowFrame::GetInstance()->SetScene(new StartScene());
}

void SceneChanger::ChangeEditScene()
{
	WindowFrame::GetInstance()->SetScene(new EditerScene());
}
