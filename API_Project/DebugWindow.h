#pragma once
class DebugWindow : public Component
{
private:
	static DebugWindow* m_Pthis;
	string m_text;
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
};

