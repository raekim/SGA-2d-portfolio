#pragma once
class PlaceableObject;
class GoalFlag;
class Map
{
	int							m_paperWidth;							// 오브젝트를 놓을 수 있는 종이의 가로칸 수
	int							m_paperHeight;							// 오브젝트를 놓을 수 있는 종이의 세로칸 수
	float						m_cellSize;								// 종이의 한 칸 가로(세로)길이
	int							m_zeroHeightPoint, m_zeroWidthPoint;	// 격자칸의 0,0 (맨 왼쪽 아래 부분) 위치

	Sprite*						m_mapForeground;						// 맵 포어그라운드 이미지
	Sprite*						m_mapBackground;						// 맵 백그라운드 이미지
	Sprite*						m_mapPaper;								// 맵툴모드에서 쓰이는 격자 종이 이미지
	vector<PlaceableObject*>	m_mapBlocks;							// 맵 지형

	vector<PlaceableObject*>	m_placedObjects;						// 맵 상에 놓여진 오브젝트들
	GoalFlag*					m_goalFlag;								// 골인 지점 깃발

	vector<vector<bool>>*		m_vecPaperCellMark;						// 오브젝트를 놓을 수 있는 종이의 어떤 칸에 오브젝트가 놓여있나 표시. (m_paperHeight)x(m_paperWidth) 크기임
public:
	Map();
	~Map();

	void Init();
	void Update(vector<vector<PlaceableObject*>>& objList);
	void RenderPlayMode();			// 플레이모드 맵 렌더
	void RenderMapToolMode();		// 맵툴모드 맵 렌더
	void Release();

	bool GetCellStatus(int h, int w);
	void SetCellStatus(int h, int w, bool val);
	pair<int, int> PosToIndex(D3DXVECTOR2 pos);
	D3DXVECTOR2 IndexToPos(pair<int, int> index);

	vector<PlaceableObject*>& GetPlacedObjects() { return m_placedObjects; }
};

