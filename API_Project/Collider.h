#pragma once

class Collider : public Component
{
protected:
	Vector2D m_colSize = { 0.f,0.f };
	Vector2D m_colOffset= { 0.f,0.f };
	vector<Collider*>* m_ColObjVec = nullptr;

	virtual void ColInit() abstract;
	virtual void ColRelease() abstract;

	bool m_isTrigger = false;
public:
	void Start() final;
	void Update() final;
	Vector2D& ColSize();
	Vector2D& ColOffset();
	vector<Collider*>* VecCol();
	void Initialize() final;
	void Release() final;
	virtual void DrawCollider();
	void SetTrigger(bool b);
	bool GetTrigger();
};


