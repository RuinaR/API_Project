#pragma once

class Collider;
class BoxCollider;

class CollisionManager
{
private:
	static CollisionManager* m_Pthis;
	vector<Collider*>* m_objVec = nullptr;
public:
	static void Create();
	static CollisionManager* GetInstance();
	static void Destroy();
public:
	void AddCollider(Collider* col);
	bool UnregisterCollider(Collider* col);
	void Update();
};

