#pragma once
class Rigidbody : public Component
{
private:
	float m_gravity = 2000.0f;
	float m_friction = 0.5f;
	bool m_isOnLand = false;
	Vector2D m_velocity;
	BoxCollider* m_box = nullptr;
	BOOL SetNoIntersect(const LPRECT pHold, LPRECT pRect);
private:
	void Initialize() override;
	void Release() override;
	void Start() override;
	void Update() override;
protected:
	void CollisionEnter(Collider* other) override;
	void CollisionExit(Collider* other) override;
	void Collision(Collider* other) override;
public:
	void SetGravity(float g);
	void SetFriction(float f);
	void AddForce(Vector2D vec);
	bool GetIsOnLand();
	Vector2D GetVelocity();
};

