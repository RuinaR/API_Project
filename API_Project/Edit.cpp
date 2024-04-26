#include "pch.h"
#include "Edit.h"


vector<string> Edit::ReadMapData(string mapName)
{
    m_mapName = mapName;
    char buffer[MAX_PATH];
    vector<string> mapData;
    GetCurrentDirectoryA(MAX_PATH, buffer);
    string currentDirectory = buffer;

    // 맵 파일 경로 설정
    string mapFilePath = currentDirectory + "\\Map\\" + mapName + ".txt";

    // 파일 열기
    ifstream inFile(mapFilePath);
    if (!inFile) {
        cout << "파일이 존재하지 않음, 새 맵 파일을 만듭니다" << endl;
        return mapData;
    }

    // 파일에서 숫자들을 2차원 배열로 읽어오기
    string line;
    while (getline(inFile, line)) 
    {
        mapData.push_back(line);
    }
    // 파일 닫기
    inFile.close();
    return mapData;
}

void Edit::WriteMapData()
{
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    string currentDirectory = buffer;

    // 맵 파일 경로 설정
    string mapFilePath = currentDirectory + "\\Map\\" + m_mapName + ".txt";
    ofstream file(mapFilePath);

    // 파일이 존재하지 않는 경우 새로운 파일 생성
    if (!file.is_open()) {
        cout << "파일을 생성할 수 없습니다." << endl;
        return;
    }

    vector<string> vStr;
    for (int i = 0; i < m_mapTypeData.size(); i++)
    {
        string row = "";
        for (int j = 0; j < m_mapTypeData[i].size(); j++)
        {
            row.append(to_string((int)m_mapTypeData[i][j]));
        }
        vStr.push_back(row);
    }

    // 데이터 쓰기
    for (const auto& line : vStr) {
        file << line << endl;
    }
    

    // 파일 닫기
    file.close();

    cout << "파일에 데이터를 성공적으로 썼습니다." << endl;
}

GameObject* Edit::DrawMap(MapType t, int i, int j)
{
    GameObject* obj = nullptr;
    switch (t)
    {
    case MapType::None:
    {
        return nullptr;
    }
    break;
    case MapType::Player:
    {
        obj = new GameObject();
        obj->AddComponent(new BitmapRender(m_player));
        obj->Size() = { UNITSIZE, UNITSIZE};
        obj->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2 ,(double)UNITSIZE * j + UNITSIZE / 2 });
        obj->InitializeSet();
    }
    break;
    case MapType::Block:
    {
        obj = new GameObject();
        obj->AddComponent(new BitmapRender(m_land));
        obj->Size() = { UNITSIZE, UNITSIZE};
        obj->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2 ,(double)UNITSIZE * j + UNITSIZE / 2 });
        obj->InitializeSet();
    }
    break;
    case MapType::DefaultMon:
    {
        obj = new GameObject();
        obj->AddComponent(new BitmapRender(m_defaultObj));
        obj->Size() = { UNITSIZE, UNITSIZE};
        obj->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2 ,(double)UNITSIZE * j + UNITSIZE / 2 });
        obj->InitializeSet();
    }
    break;
    case MapType::SwordMon:
    {
        obj = new GameObject();
        obj->AddComponent(new BitmapRender(m_swordObj));
        obj->Size() = { UNITSIZE, UNITSIZE};
        obj->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2 ,(double)UNITSIZE * j + UNITSIZE / 2 });
        obj->InitializeSet();
    }
    break;
    case MapType::StoneMon:
    {
        obj = new GameObject();
        obj->AddComponent(new BitmapRender(m_stoneObj));
        obj->Size() = { UNITSIZE, UNITSIZE};
        obj->SetPosition({ (double)UNITSIZE * i + UNITSIZE / 2 ,(double)UNITSIZE * j + UNITSIZE / 2 });
        obj->InitializeSet();
    }
    break;
    }
    return obj;
}

void Edit::SelectNone()
{
    m_select = MapType::None;
}

void Edit::SelectLand()
{
    m_select = MapType::Block;
}

void Edit::SelectDefaultMon()
{
    m_select = MapType::DefaultMon;
}

void Edit::SelectSwordMon()
{
    m_select = MapType::SwordMon;
}

void Edit::SelectStoneMon()
{
    m_select = MapType::StoneMon;
}

void Edit::SelectPlayer()
{
    m_select = MapType::Player;
}

void Edit::InitMap()
{
    for (int i = 0; i < m_count; ++i)
    {
        for (int j = 0; j < m_count; ++j)
        {
            if (m_mapData[i][j])
            {
                m_mapData[i][j]->SetDestroy(true);
                m_mapData[i][j] = nullptr;
            }
            m_mapTypeData[i][j] = MapType::None;
        }
    }
}

void Edit::Initialize()
{
    m_land = AnimationManager::LoadHBitmap("Bitmaps\\obj\\land");
    m_bg = AnimationManager::LoadHBitmap("Bitmaps\\obj\\BG");
    m_defaultObj = AnimationManager::LoadHBitmap("Bitmaps\\obj\\defaultObj");
    m_swordObj = AnimationManager::LoadHBitmap("Bitmaps\\obj\\swordObj");
    m_stoneObj = AnimationManager::LoadHBitmap("Bitmaps\\obj\\stoneObj");
    m_player = AnimationManager::LoadHBitmap("Bitmaps\\obj\\player");

    for (int i = 0; i < (int)MapType::max; i++)
    {
        GameObject* obj = new GameObject();
        m_selectBtn[i] = new ColorButton();
        obj->AddComponent(m_selectBtn[i]);
        m_selectBtn[i]->SetUIPos({ 200.0 + i * 100, 10 });
        m_selectBtn[i]->SetUISize({ 90,50 });
        obj->SetOrderInLayer(10);
        obj->InitializeSet();
    }
    m_selectBtn[(int)MapType::None]->SetText(TEXT("빈곳"));
    m_selectBtn[(int)MapType::Block]->SetText(TEXT("땅"));
    m_selectBtn[(int)MapType::Player]->SetText(TEXT("커비"));
    m_selectBtn[(int)MapType::DefaultMon]->SetText(TEXT("기본 몹"));
    m_selectBtn[(int)MapType::SwordMon]->SetText(TEXT("소드 몹"));
    m_selectBtn[(int)MapType::StoneMon]->SetText(TEXT("스톤 몹"));

    GameObject* obj = new GameObject();
    m_InitMapBtn = new ColorButton();
    obj->AddComponent(m_InitMapBtn);
    m_InitMapBtn->SetUIPos({800, 10});
    m_InitMapBtn->SetUISize({ 90,50 });
    obj->SetOrderInLayer(10);
    obj->InitializeSet();
    m_InitMapBtn->SetText(TEXT("초기화"));
    m_InitMapBtn->SetEvent(bind(&Edit::InitMap, this));

    m_selectBtn[(int)MapType::None]->SetEvent(bind(&Edit::SelectNone, this));
    m_selectBtn[(int)MapType::Block]->SetEvent(bind(&Edit::SelectLand, this));
    m_selectBtn[(int)MapType::Player]->SetEvent(bind(&Edit::SelectPlayer, this));
    m_selectBtn[(int)MapType::DefaultMon]->SetEvent(bind(&Edit::SelectDefaultMon, this));
    m_selectBtn[(int)MapType::SwordMon]->SetEvent(bind(&Edit::SelectSwordMon, this));
    m_selectBtn[(int)MapType::StoneMon]->SetEvent(bind(&Edit::SelectStoneMon, this));


    m_mapData = vector<vector<GameObject*>>(m_count);
    m_mapTypeData = vector<vector<MapType>>(m_count);
    for (int i = 0; i < m_count; i++)
    {
        m_mapData[i] = vector<GameObject*>(m_count);
        m_mapTypeData[i] = vector<MapType>(m_count);
    }

}

void Edit::Release()
{
    AnimationManager::ReleaseHBitmap(m_land);
    AnimationManager::ReleaseHBitmap(m_bg);
    AnimationManager::ReleaseHBitmap(m_defaultObj);
    AnimationManager::ReleaseHBitmap(m_swordObj);
    AnimationManager::ReleaseHBitmap(m_stoneObj);
    AnimationManager::ReleaseHBitmap(m_player);

    WriteMapData();
}

void Edit::Start()
{
    RECT rect;
    GetClientRect(WindowFrame::GetInstance()->GetHWND(), &rect);
    Camera::GetInstance()->SetPos(UNITSIZE + UNITSIZE / 2, 0);
}

void Edit::Update()
{
	for (int i = 0; i < m_count; i++)
	{
        MoveToEx(WindowFrame::GetInstance()->GetBuffer()->GetHDC(), 
            i * UNITSIZE - UNITSIZE / 2 - Camera::GetInstance()->GetPos().x, -Camera::GetInstance()->GetPos().y, NULL);
        LineTo(WindowFrame::GetInstance()->GetBuffer()->GetHDC(), 
            i * UNITSIZE - UNITSIZE / 2 - Camera::GetInstance()->GetPos().x, UNITSIZE * 100 - Camera::GetInstance()->GetPos().y);
	}
    for (int i = 0; i < m_count; i++)
    {
        MoveToEx(WindowFrame::GetInstance()->GetBuffer()->GetHDC(), 
            - Camera::GetInstance()->GetPos().x, i * UNITSIZE - UNITSIZE / 2 - Camera::GetInstance()->GetPos().y, NULL);
        LineTo(WindowFrame::GetInstance()->GetBuffer()->GetHDC(), 
            UNITSIZE * 100 - Camera::GetInstance()->GetPos().x, i * UNITSIZE - UNITSIZE / 2 - Camera::GetInstance()->GetPos().y);
    }

	int cameraSpd = 10;
	if (GetAsyncKeyState(0x57)) //W
	{
		if (Camera::GetInstance()->GetPos().y - cameraSpd >= 0)
			Camera::GetInstance()->SetPos(Camera::GetInstance()->GetPos().x, Camera::GetInstance()->GetPos().y - cameraSpd);
	}
	if (GetAsyncKeyState(0x53)) //S
	{
		if (Camera::GetInstance()->GetPos().y + cameraSpd <= UNITSIZE * m_count - UNITSIZE * 15)
			Camera::GetInstance()->SetPos(Camera::GetInstance()->GetPos().x, Camera::GetInstance()->GetPos().y + cameraSpd);
	}
	if (GetAsyncKeyState(0x41)) //A
	{
		if (Camera::GetInstance()->GetPos().x - cameraSpd >= UNITSIZE + UNITSIZE / 2)
			Camera::GetInstance()->SetPos(Camera::GetInstance()->GetPos().x - cameraSpd, Camera::GetInstance()->GetPos().y);
	}
	if (GetAsyncKeyState(0x44)) //D
	{
		if (Camera::GetInstance()->GetPos().x + cameraSpd <= UNITSIZE * m_count - UNITSIZE * 20)
			Camera::GetInstance()->SetPos(Camera::GetInstance()->GetPos().x + cameraSpd, Camera::GetInstance()->GetPos().y);
	}


	if (Mouse::GetInstance()->IsLeftDown())
    {
        if (Mouse::GetInstance()->GetPos().Y < UNITSIZE)
            return;

        int x = Mouse::GetInstance()->GetPos().X + Camera::GetInstance()->GetPos().x - UNITSIZE / 2;
        int y = Mouse::GetInstance()->GetPos().Y + Camera::GetInstance()->GetPos().y - UNITSIZE / 2;

        int indexX = x / UNITSIZE;
        int indexY = y / UNITSIZE;

		if (m_mapTypeData[indexY][indexX] != m_select)
		{
            if (m_mapTypeData[indexY][indexX] == MapType::None && m_select == MapType::None)
                return;

            if (m_mapTypeData[indexY][indexX] != MapType::None)
            {
                m_mapData[indexY][indexX]->SetDestroy(true);
                if (m_select == MapType::None)
                {
                    m_mapData[indexY][indexX] = nullptr;
                    m_mapTypeData[indexY][indexX] = MapType::None;
                    return;
                }
            }

            GameObject* newObj = new GameObject();
			switch (m_select)
			{
			case MapType::None:
				break;
			case MapType::Block:
                newObj->AddComponent(new BitmapRender(m_land));
				break;
			case MapType::Player:
                newObj->AddComponent(new BitmapRender(m_player));
                for (int i = 0; i < m_count; ++i)
                {
                    for (int j = 0; j < m_count; ++j)
                    {
                        if (m_mapTypeData[i][j] == MapType::Player)
                        {
                            m_mapData[i][j]->SetDestroy(true);
                            m_mapData[i][j] = nullptr;
                            m_mapTypeData[i][j] = MapType::None;
                        }
                    }
                }
				break;
            case MapType::DefaultMon:
                newObj->AddComponent(new BitmapRender(m_defaultObj));
                break;
            case MapType::SwordMon:
                newObj->AddComponent(new BitmapRender(m_swordObj));
                break;
            case MapType::StoneMon:
                newObj->AddComponent(new BitmapRender(m_stoneObj));
                break;
			}      
            
            newObj->Size() = { UNITSIZE, UNITSIZE };
            newObj->SetPosition({ (double)UNITSIZE * indexX + UNITSIZE / 2 ,(double)UNITSIZE * indexY + UNITSIZE / 2 });
            newObj->InitializeSet();
            m_mapData[indexY][indexX] = newObj;
            m_mapTypeData[indexY][indexX] = m_select;
		}
	}
}

void Edit::SetMap(string mapName)
{
    WindowFrame::GetInstance()->GetBuffer()->SetBG(m_bg);

    vector<string> strMapData = ReadMapData(mapName);
    if (strMapData.empty())
        return;

    for (int i = 0; i < m_count; ++i)
    {
        vector<GameObject*> row;
        for (int j = 0; j < m_count; ++j)
        {
            m_mapData[i][j] = DrawMap((MapType)(strMapData[i][j] - '0'), j, i);
            m_mapTypeData[i][j] = (MapType)(strMapData[i][j] - '0'); 
            cout << "Draw Tile Type : " << to_string(strMapData[i][j] - '0') << endl;
        }
    }
}