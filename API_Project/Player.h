#pragma once
#include "Component.h"
#include "Rigidbody.h"

enum class PlayerArrow
{
	left,
	right,
	max
};

enum class PlayerAState
{
	idle,
	walk,
	jump,
	max
};

enum class PlayerMode
{
	mDefault,
	max
};

class Player : public Component
{
private:
	Rigidbody* m_rig = nullptr;
	AnimationRender* m_ar = nullptr;
	Animation m_arrAnim[(int)PlayerMode::max][(int)PlayerArrow::max][(int)PlayerAState::max];
	PlayerMode m_mode;
	PlayerArrow m_arrow;
	PlayerAState m_state;
	void UpdateAnim(bool isOneTime);
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