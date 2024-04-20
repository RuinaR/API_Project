#pragma once
#include "pch.h"
#include "Player.h"
class StageMaker : public Component
{
protected:
	vector<string> ReadMapData(string mapName);
	void MakeMap(MapType t, int i, int j);

	HBITMAP m_bg = NULL;
	HBITMAP m_land = NULL;
	HBITMAP m_swordObj = NULL;
	HBITMAP m_stoneObj = NULL;
	HBITMAP m_defaultObj = NULL;

	Player* m_player = nullptr;
	GameObject* m_playerObj = nullptr;
public:
	void StageStart();
	void SetMap(string mapName);
	void Initialize() override;
	void Release() override;
	void Start() override;
	void Update() override;
};

