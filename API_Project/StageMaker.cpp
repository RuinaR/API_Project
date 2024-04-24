#include "pch.h"
#include "StageMaker.h"
#include "Player.h"
#include "BoxCollider.h"
#include "ChangeObject.h"

bool EqualFloat(float f1, float f2, float d)
{
	if (f1 + d > f2 && f1 - d < f2)
		return true;

	return false;
}

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
        mapData.push_back('0' + line);
    }

    // 파일 닫기
    inFile.close();
    return mapData;
}

void StageMaker::MakeMap(MapType t, int i, int j, vector<GameObject*>* rowGroup, vector<bool>* colRow)
{
	switch (t)
	{
	case MapType::None:
    {
        rowGroup->push_back(nullptr);
        colRow->push_back(false);
    }
		break;
	case MapType::Player:
    {
        m_playerObj->SetPosition({ (double)UNITSIZE * i,(double)UNITSIZE * j });
        rowGroup->push_back(m_playerObj);
        colRow->push_back(false);
	}
	break;
	case MapType::Block: //가로줄 콜라이더를 계산해서 합친 상태로 생성
	{
		GameObject* obj = new GameObject();
		obj->SetTag(TAG_LAND);
		obj->SetPosition({ (double)UNITSIZE * i,(double)UNITSIZE * j });
		obj->Size() = { UNITSIZE, UNITSIZE };
		obj->AddComponent(new BitmapRender(m_land));
        if (!rowGroup->empty() && (rowGroup->back() != nullptr && rowGroup->back()->GetTag() == TAG_LAND))
        {
            int startIdx = rowGroup->size() - 1;
            int endIdx = 0;
            for (int k = startIdx; k >= 0; k--)
            {
                if ((*rowGroup)[k] == nullptr || (*rowGroup)[k]->GetTag() != TAG_LAND)
				{
					endIdx = k + 1;
                    BoxCollider* bo = (*rowGroup)[endIdx]->GetComponent<BoxCollider>();
                    if (bo == nullptr)
                    {
                        BoxCollider* newBo = new BoxCollider();
                        (*rowGroup)[endIdx]->AddComponent(newBo);
                        (*rowGroup)[endIdx]->SetOrderInLayer(1);
                        newBo->ColSize() =
                        { (double)(UNITSIZE * (startIdx - endIdx + 2)) ,(double)UNITSIZE };
                    }
                    else
                    {
                        bo->ColSize() =
                        { (double)(UNITSIZE * (startIdx - endIdx + 2)) ,(double)UNITSIZE };
                    }
                    for (int q = endIdx; q < startIdx + 1; q++)
                    {
                        (*colRow)[q] = true;
                    }
                    if (startIdx + 1 >= colRow->size())
                        colRow->push_back(true);
                    else
                        (*colRow)[startIdx + 1] = true;

					break;
				}
			}
		}
		obj->InitializeSet();
		rowGroup->push_back(obj);
		if (rowGroup->size() > colRow->size())
			colRow->push_back(false);
	}
	break;
	case MapType::DefaultMon:
	{
        GameObject* defaultMon = new GameObject();
       defaultMon->SetTag(TAG_MONSTER);
       defaultMon->SetOrderInLayer(2);
       defaultMon->Size() = { UNITSIZE / 2, UNITSIZE / 2 };
       defaultMon->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2 ,(double)UNITSIZE * j + UNITSIZE / 2 });
       defaultMon->AddComponent(new ChangeObject(PlayerMode::mDefault, m_player));
       defaultMon->AddComponent(new BitmapRender(m_defaultObj));
       defaultMon->AddComponent(new BoxCollider());
       defaultMon->InitializeSet();
       rowGroup->push_back(defaultMon);
       colRow->push_back(false);
    }
        break;
    case MapType::SwordMon:
    {
        GameObject* swordMon = new GameObject();
        swordMon->SetTag(TAG_MONSTER);
        swordMon->SetOrderInLayer(2);
        swordMon->Size() = { UNITSIZE / 2, UNITSIZE / 2 };
        swordMon->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2,(double)UNITSIZE * j + UNITSIZE / 2 });
        swordMon->AddComponent(new ChangeObject(PlayerMode::mSword, m_player));
        swordMon->AddComponent(new BitmapRender(m_swordObj));
        swordMon->AddComponent(new BoxCollider());
        swordMon->InitializeSet();
        rowGroup->push_back(swordMon);
        colRow->push_back(false);
    }
	break;
	case MapType::StoneMon:
	{
		GameObject* stoneMon = new GameObject();
		stoneMon->SetTag(TAG_MONSTER);
        stoneMon->SetOrderInLayer(2);
		stoneMon->Size() = { UNITSIZE / 2, UNITSIZE / 2 };
		stoneMon->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2,(double)UNITSIZE * j + UNITSIZE / 2 });
		stoneMon->AddComponent(new ChangeObject(PlayerMode::mStone, m_player));
		stoneMon->AddComponent(new BitmapRender(m_stoneObj));
		stoneMon->AddComponent(new BoxCollider());
		stoneMon->InitializeSet();
        rowGroup->push_back(stoneMon);
        colRow->push_back(false);
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
    for (vector<vector<bool>>::iterator itr = m_colInfo.begin(); itr != m_colInfo.end(); itr++)
        itr->clear();
    m_colInfo.clear();

    WindowFrame::GetInstance()->GetBuffer()->SetBG(m_bg);
    vector<string> mapData = ReadMapData(mapName);
    for (int i = 0; i < mapData.size(); ++i)
    {
        vector<GameObject*> row;
        vector<bool> colrow;
        for (int j = 0; j < mapData[i].size(); ++j) 
        {
            MakeMap((MapType)(mapData[i][j] - '0'), j, i, &row, &colrow);
        }
        m_mapObj.push_back(row);
        m_colInfo.push_back(colrow);
    }
    
    for (int i = 0; i < m_mapObj.size(); i++) //나머지 세로줄 콜라이더를 합쳐서 생성하는 작업
    {
        for (int j = 0; j < m_mapObj[i].size(); j++)
        {
            if (m_mapObj[i][j] != nullptr && 
                m_mapObj[i][j]->GetTag() == TAG_LAND && 
                m_mapObj[i][j]->GetComponent<BoxCollider>() == nullptr &&
                m_colInfo[i][j] == false)
            {
                int cnt = 1;
                m_colInfo[i][j] = true;
                for (int k = i + 1; k < m_mapObj.size(); k++)
                {
                    if (m_mapObj[k][j] != nullptr &&
                        m_mapObj[k][j]->GetTag() == TAG_LAND &&
                        m_mapObj[k][j]->GetComponent<BoxCollider>() == nullptr &&
                        m_colInfo[k][j] == false)
                    {
                        cnt++;
                        m_colInfo[k][j] = true;
                    }
                    else
                        break;
                }
                BoxCollider* newBo = new BoxCollider();
                m_mapObj[i][j]->AddComponent(newBo);
                newBo->ColSize() = { UNITSIZE, (double)(UNITSIZE * cnt) };
                m_mapObj[i][j]->SetOrderInLayer(1);
            }
        }
    }

    //가로줄 콜라이더끼리 마지막으로 합치는 작업(가로줄 우선이므로 세로줄끼리 합치는 작업은 필요없음)
    for (int i = 0; i < m_mapObj.size(); i++)
    {
        for (int j = 0; j < m_mapObj[i].size(); j++)
        {
            if (m_mapObj[i][j] == nullptr || m_mapObj[i][j]->GetTag() != TAG_LAND)
                continue;
            BoxCollider* bo = m_mapObj[i][j]->GetComponent<BoxCollider>();
			int cnt = 1;
			if (bo != nullptr && EqualFloat(bo->ColSize().y, UNITSIZE, 0.1f))
			{
				for (int k = i + 1; k < m_mapObj.size(); k++)
				{
                    if (m_mapObj[k][j] == nullptr || m_mapObj[k][j]->GetTag() != TAG_LAND)
                        break;
					BoxCollider* bo2 = m_mapObj[k][j]->GetComponent<BoxCollider>();
					if (bo2 == nullptr || !EqualFloat(bo->ColSize().x, bo2->ColSize().x, 0.1f))
					{
						break;
					}
					else
					{
						m_mapObj[k][j]->DeleteComponent(bo2);
                        m_mapObj[k][j]->SetOrderInLayer(0);
                        cnt++;
					}
				}
                bo->ColSize() = { bo->ColSize().x , (double)(UNITSIZE * cnt) };
                bo->GetGameObject()->SetOrderInLayer(1);
			}
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
    m_playerObj->SetOrderInLayer(5);

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
