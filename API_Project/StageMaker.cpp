#include "pch.h"
#include "StageMaker.h"
#include "Player.h"
#include "BoxCollider.h"
#include "ChangeObject.h"

vector<string> StageMaker::ReadMapData(string mapName)
{
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    string currentDirectory = buffer;

    // 맵 파일 경로 설정
    string mapFilePath = currentDirectory + "\\Map\\" + mapName + ".txt";

    // 파일 열기
    ifstream inFile(mapFilePath);
    if (!inFile) {
        cerr << "파일을 열 수 없습니다." << endl;
        exit(1);
    }

    // 파일에서 숫자들을 2차원 배열로 읽어오기
    vector<string> mapData;
    string line;
    while (getline(inFile, line)) 
    {
        mapData.push_back(line);
    }

    // 파일 닫기
    inFile.close();
    return mapData;
}

void StageMaker::MakeMap(MapType t, int i, int j, vector<GameObject*>* rowGroup)
{
	switch (t)
	{
	case MapType::None:
    {
        rowGroup->push_back(nullptr);
    }
		break;
	case MapType::Player:
    {
        m_playerObj->SetPosition({ (double)UNITSIZE * i,(double)UNITSIZE * j });
        rowGroup->push_back(m_playerObj);
	}
	break;
	case MapType::Block:
	{
		GameObject* obj = new GameObject();
		obj->SetTag(TAG_LAND);
		obj->SetPosition({ (double)UNITSIZE * i,(double)UNITSIZE * j });
		obj->Size() = { UNITSIZE, UNITSIZE };
		obj->AddComponent(new BitmapRender(m_land));
		if (rowGroup->empty() || (rowGroup->back() == nullptr || rowGroup->back()->GetTag() != TAG_LAND))
			obj->AddComponent(new BoxCollider());
        else
        {
            int startIdx = rowGroup->size() - 1;
            int endIdx = 0;
            for (int k = startIdx; k >= 0; k--)
            {
                if ((*rowGroup)[k] == nullptr || (*rowGroup)[k]->GetTag() != TAG_LAND)
				{
					endIdx = k + 1;
					break;
				}
			}
			if ((*rowGroup)[endIdx] != nullptr)
				(*rowGroup)[endIdx]->GetComponent<BoxCollider>()->ColSize() = 
            { (double)(UNITSIZE * (startIdx - endIdx + 2)) ,(double)UNITSIZE };
		}
		obj->InitializeSet();
		rowGroup->push_back(obj);
	}
	break;
	case MapType::DefaultMon:
	{
        GameObject* defaultMon = new GameObject();
       defaultMon->SetTag(TAG_MONSTER);
       defaultMon->Size() = { UNITSIZE / 2, UNITSIZE / 2 };
       defaultMon->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2 ,(double)UNITSIZE * j + UNITSIZE / 2 });
       defaultMon->AddComponent(new ChangeObject(PlayerMode::mDefault, m_player));
       defaultMon->AddComponent(new BitmapRender(m_defaultObj));
       defaultMon->AddComponent(new BoxCollider());
       defaultMon->InitializeSet();
       rowGroup->push_back(defaultMon);
    }
        break;
    case MapType::SwordMon:
    {
        GameObject* swordMon = new GameObject();
        swordMon->SetTag(TAG_MONSTER);
        swordMon->Size() = { UNITSIZE / 2, UNITSIZE / 2 };
        swordMon->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2,(double)UNITSIZE * j + UNITSIZE / 2 });
        swordMon->AddComponent(new ChangeObject(PlayerMode::mSword, m_player));
        swordMon->AddComponent(new BitmapRender(m_swordObj));
        swordMon->AddComponent(new BoxCollider());
        swordMon->InitializeSet();
        rowGroup->push_back(swordMon);
    }
	break;
	case MapType::StoneMon:
	{
		GameObject* stoneMon = new GameObject();
		stoneMon->SetTag(TAG_MONSTER);
		stoneMon->Size() = { UNITSIZE / 2, UNITSIZE / 2 };
		stoneMon->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2,(double)UNITSIZE * j + UNITSIZE / 2 });
		stoneMon->AddComponent(new ChangeObject(PlayerMode::mStone, m_player));
		stoneMon->AddComponent(new BitmapRender(m_stoneObj));
		stoneMon->AddComponent(new BoxCollider());
		stoneMon->InitializeSet();
        rowGroup->push_back(stoneMon);
	}
        break;
    }
}

void StageMaker::StageStart()
{
    if (m_playerObj->GetActive() == false)
        m_playerObj->SetActive(true);
}

void StageMaker::SetMap(string mapName)
{
	for (vector<vector<GameObject*>>::iterator itr = m_mapObj.begin(); itr != m_mapObj.end(); itr++)
		itr->clear();
	m_mapObj.clear();

    WindowFrame::GetInstance()->GetBuffer()->SetBG(m_bg);
    vector<string> mapData = ReadMapData(mapName);
    for (int i = 0; i < mapData.size(); ++i)
    {
        vector<GameObject*> row;
        for (int j = 0; j < mapData[i].size(); ++j) 
        {
            MakeMap((MapType)(mapData[i][j] - '0'), j, i, &row);
        }
        m_mapObj.push_back(row);
    }
}

void StageMaker::Initialize()
{
    m_land = AnimationManager::LoadHBitmap("Bitmaps\\obj\\land");
    m_bg = AnimationManager::LoadHBitmap("Bitmaps\\obj\\BG");
    m_defaultObj = AnimationManager::LoadHBitmap("Bitmaps\\obj\\defaultObj");
    m_swordObj = AnimationManager::LoadHBitmap("Bitmaps\\obj\\swordObj");
    m_stoneObj = AnimationManager::LoadHBitmap("Bitmaps\\obj\\stoneObj");

    m_playerObj = new GameObject();
    m_player = new Player();
    m_playerObj->AddComponent(m_player);
    m_playerObj->InitializeSet();
    m_playerObj->SetOrderInLayer(10);

    m_playerObj->SetActive(false);
}

void StageMaker::Release()
{

    AnimationManager::ReleaseHBitmap(m_land);
    AnimationManager::ReleaseHBitmap(m_bg);
    AnimationManager::ReleaseHBitmap(m_defaultObj);
    AnimationManager::ReleaseHBitmap(m_swordObj);
    AnimationManager::ReleaseHBitmap(m_stoneObj);
}

void StageMaker::Start()
{
}

void StageMaker::Update()
{
   
}
