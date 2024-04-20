#pragma once
#include "pch.h"
#include "Player.h"

class ChangeObject : public Component
{
protected:
	PlayerMode m_mode = PlayerMode::mDefault;\
	Player* m_player = nullptr;
	float m_area = 300.0f;
	float m_speed = 300.0f;

	virtual void CollisionEnter(Collider* other) {};
	virtual void CollisionExit(Collider* other) {};
	virtual void Collision(Collider* other) {};
public:
	ChangeObject(PlayerMode mode, Player* player);	
	virtual ~ChangeObject();
	void Initialize() override;
	void Release() override;
	void Start() override;
	void Update() override;

	PlayerMode GetMode();
};

