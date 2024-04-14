#include "pch.h"
#include "GameObject.h"
GameObject::GameObject() {
    m_vecComponent = new vector<Component*>();
}

GameObject::~GameObject() {
    cout << "~GameObject()" << endl;
}

Vector2D& GameObject::Position() {
    return m_position;
}

Vector2D& GameObject::Size() {
    return m_size;
}

float& GameObject::Angle()
{
    return m_angle;
}

void GameObject::SetDestroy(bool destroy) {
    m_isDestroy = destroy;
}

bool GameObject::GetDestroy() {
    return m_isDestroy;
}

void GameObject::SetTag(string tag) {
    m_tag = tag;
}

string GameObject::GetTag() {
    return m_tag;
}

void GameObject::SetActive(bool isActive) {
    m_setActive = isActive;
}

bool GameObject::GetActive() {
    return m_setActive;
}

void GameObject::SetOrderInLayer(float value) {
    m_orderInLayer = value;
    ObjectManager::GetInstance()->UnregisterObject(this);
    ObjectManager::GetInstance()->RegisterObject(this);
}

float GameObject::GetOrderInLayer() {
    return m_orderInLayer;
}

Component* GameObject::AddComponent(Component* component) {
    if (component) {
        component->InitGameObj(this);
        m_vecComponent->push_back(component);
        component->Initialize();
        if (ObjectManager::GetInstance()->FindObject(this)) {
            component->Start();
        }
        return component;
    }
    return nullptr;
}

void GameObject::DeleteComponent(Component* component) {
    for (vector<Component*>::iterator itr = m_vecComponent->begin(); itr != m_vecComponent->end(); itr++) {
        if ((*itr) == component) {
            (*itr)->Release();
            delete(*itr);
            (*itr) = nullptr;
            m_vecComponent->erase(itr);
            return;
        }
    }
}

vector<Component*>* GameObject::GetComponentVec() {
    return m_vecComponent;
}

void GameObject::InitializeSet() {
    m_isDestroy = false;
	ObjectManager::GetInstance()->AddObject(this);
}

void GameObject::Release() {

	for (vector<Component*>::iterator itr = m_vecComponent->begin(); itr != m_vecComponent->end(); itr++)
	{
		(*itr)->Release();
		delete(*itr);
		(*itr) = nullptr;
	}

	delete m_vecComponent;
    m_vecComponent = nullptr;
}

void GameObject::Start() {
    for (vector<Component*>::iterator itr = m_vecComponent->begin(); itr != m_vecComponent->end(); itr++)
        (*itr)->Start();
}

void GameObject::Update() {
    if (!m_setActive)
        return;

    for (vector<Component*>::iterator itr = m_vecComponent->begin(); itr != m_vecComponent->end(); itr++)
        (*itr)->Update();
}