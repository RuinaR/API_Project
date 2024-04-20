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

void StageMaker::MakeMap(MapType t, int i, int j)
{
	switch (t)
	{
	case MapType::None:
    {

    }
		break;
	case MapType::Player:
    {
        m_playerObj->SetPosition({ (double)UNITSIZE * i,(double)UNITSIZE * j });
    }
		break;
	case MapType::Block:
    {
        GameObject* obj = new GameObject();
        obj->SetTag(TAG_LAND);
        obj->SetPosition({ (double)UNITSIZE * i,(double)UNITSIZE * j });
        obj->Size() = { UNITSIZE, UNITSIZE };
        obj->AddComponent(new BitmapRender(m_land));
        obj->AddComponent(new BoxCollider());
        obj->InitializeSet();
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
    WindowFrame::GetInstance()->GetBuffer()->SetBG(m_bg);
    vector<string> mapData = ReadMapData(mapName);
    for (int i = 0; i < mapData.size(); ++i)
    {
        for (int j = 0; j < mapData[i].size(); ++j) 
        {
            MakeMap((MapType)(mapData[i][j] - '0'), j, i);
        }
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
