#pragma once
#include "Component.h"
#include "structs.h"
class GameObject
{
protected:
    bool m_isDestroy = false;
    bool m_setActive = true;
    string m_tag = "";
    Vector2D m_position = { 0 };
    Vector2D m_size = { 0 };
    float m_angle = 0.0f;
    float m_orderInLayer = 0.0f;
    vector<Component*>* m_vecComponent = nullptr;

public:
    GameObject();
    virtual ~GameObject();

    Vector2D& Position();
    Vector2D& Size();
    float& Angle();
    template <typename T>
    T* GetComponent() {
        for (vector<Component*>::iterator itr = m_vecComponent->begin(); itr != m_vecComponent->end(); itr++) {
            if (typeid(**itr) == typeid(T)) {
                return (T*)*itr;
            }
        }
        return nullptr;
    }

    void SetDestroy(bool destroy);
    bool GetDestroy();
    void SetTag(string tag);
    string GetTag();
    void SetActive(bool isActive);
    bool GetActive();
    void SetOrderInLayer(float value);
    float GetOrderInLayer();
    Component* AddComponent(Component* component);
    void DeleteComponent(Component* component);
    vector<Component*>* GetComponentVec();
    void InitializeSet();
    void Release();
    void Start();
    void Update();
};
