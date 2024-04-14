#include "pch.h"
#include "Component.h"
Component::Component()
{
	
}

Component::~Component()
{
	cout << "~Component()" << endl;
}

void Component::InitGameObj(GameObject* obj)
{
	m_gameObj = obj;
}

GameObject* Component::GetGameObject()
{
	return this->m_gameObj;
}
