#include "pch.h"
#include "RestartButton.h"
#include "GameScene.h"

void RestartButton::ButtonEvent()
{
	m_curColor = m_defaultColor;
	GameScene* newScene = new GameScene();
	WindowFrame::GetInstance()->SetScene(newScene);
}
