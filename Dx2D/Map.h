#pragma once
class PlaceableObject;
class GoalFlag;
class Map
{
	int							m_paperWidth;							// ������Ʈ�� ���� �� �ִ� ������ ����ĭ ��
	int							m_paperHeight;							// ������Ʈ�� ���� �� �ִ� ������ ����ĭ ��
	float						m_cellSize;								// ������ �� ĭ ����(����)����
	int							m_zeroHeightPoint, m_zeroWidthPoint;	// ����ĭ�� 0,0 (�� ���� �Ʒ� �κ�) ��ġ

	Sprite*						m_mapForeground;						// �� ����׶��� �̹���
	Sprite*						m_mapBackground;						// �� ��׶��� �̹���
	Sprite*						m_mapPaper;								// ������忡�� ���̴� ���� ���� �̹���
	vector<PlaceableObject*>	m_mapBlocks;							// �� ����

	vector<PlaceableObject*>	m_placedObjects;						// �� �� ������ ������Ʈ��
	GoalFlag*					m_goalFlag;								// ���� ���� ���

	vector<vector<bool>>*		m_vecPaperCellMark;						// ������Ʈ�� ���� �� �ִ� ������ � ĭ�� ������Ʈ�� �����ֳ� ǥ��. (m_paperHeight)x(m_paperWidth) ũ����
public:
	Map();
	~Map();

	void Init();
	void Update(vector<vector<PlaceableObject*>>& objList);
	void RenderPlayMode();			// �÷��̸�� �� ����
	void RenderMapToolMode();		// ������� �� ����
	void Release();

	bool GetCellStatus(int h, int w);
	void SetCellStatus(int h, int w, bool val);
	pair<int, int> PosToIndex(D3DXVECTOR2 pos);
	D3DXVECTOR2 IndexToPos(pair<int, int> index);

	vector<PlaceableObject*>& GetPlacedObjects() { return m_placedObjects; }
};

