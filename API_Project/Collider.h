#pragma once

class Collider : public Component
{
protected:
	Vector2D m_colSize = { 0.f,0.f };
	vector<Collider*>* m_ColObjVec = nullptr;

	virtual void ColInit() abstract;
	virtual void ColRelease() abstract;
public:
	void Start() final;
	void Update() final;
	Vector2D& ColSize();
	vector<Collider*>* VecCol();
	void Initialize() final;
	void Release() final;

	void SetCol(int w, int h);
};


