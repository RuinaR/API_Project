#pragma once
class DebugWindow : public Component
{
private:
	static DebugWindow* m_Pthis;
	string m_text;
	Vector2D m_dwSize;
	Vector2D m_dwPos;
public:
	void Initialize() override;
	void Release() override;
	void Start() override;
	void Update() override;
public:
	static DebugWindow* GetInstance();
	static void Create();
	static void Destroy();
public:
	void SetText(string text);
	void SetDWSize(Vector2D size);
	void SetDWPos(Vector2D pos);
};

