#pragma once
#include "Component.h"
#include "Rigidbody.h"
class Player : public Component
{
private:
	Rigidbody* m_rig = nullptr;
protected:
	void CollisionEnter(Collider* other) override;
	void CollisionExit(Collider* other) override;
	void Collision(Collider* other) override;
public:
	Player();
	~Player();
	void Initialize() override;
	void Release() override;
	void Start() override;
	void Update() override;
};