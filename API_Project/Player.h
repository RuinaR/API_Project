#pragma once
#include "Component.h"
#include "Rigidbody.h"
#include "pch.h"

class Player : public Component
{
protected:
	Rigidbody* m_rig = nullptr;
	AnimationRender* m_ar = nullptr;
	Animation m_arrAnim[(int)PlayerMode::max][(int)PlayerArrow::max][(int)PlayerAState::max];
	PlayerMode m_mode;
	PlayerArrow m_arrow;
	PlayerAState m_state;
	PlayerMode m_eatMode = PlayerMode::mDefault;
	Timer m_flyTimer = Timer();
	Timer m_leftKeyTimer = Timer();
	Timer m_rightKeyTimer = Timer();
	Vector2D m_dSize = { 50,50 };

	bool m_leftKeyTrigger = false;
	bool m_rightKeyTrigger = false;
	bool m_jumpFlyTrigger = false;
	bool m_atkTrigger = false;

	float m_dblTime = 0.25f;

	int m_leftKey = 0;
	int m_rightKey = 0;
	int m_jumpKey = 0;
	int m_atkKey = 0;
	int m_changeKey = 0;

	float m_speed = 250.0f;
	float m_speed_run = 500.0f;
	float m_speed_fly = 150.0f;
	float m_eatSpeed = 150.0f;
	float m_curXSpeed = 0.0f;
	float m_JumpV = 500.0f;

	float m_startGravity = 0.0f;
	float m_flyGravity = 450.0f;

	void (Player::* m_attackFunc[(int)PlayerMode::max])();
protected:
	void UpdateAnim(bool isOneTime);
	void FlyAction();
	void MoveLeft();
	void MoveRight();
	void JumpAction();
	void Idle();
protected:
	void Attack_default();
	void Attack_sword();
	void Attack_stone();
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
	PlayerAState GetState();
	PlayerArrow GetArrow();
};