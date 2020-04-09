#pragma once

class PlaceableObject;
class PlayerCursor
{	
	int					m_selectKey, m_leftMoveKey, m_rightMoveKey, m_upMoveKey, m_downMoveKey, m_flipKey; // ��Ʈ�� ����
	Sprite*				m_cursorDefaultImage;			// Ŀ�� �̹���
	Sprite*				m_cursorOutOfBoundsImage;		// �������� ���� ���ϴ� ������ Ŀ�� �̹���
	D3DXVECTOR2			m_cursorPos;					// Ŀ�� �̹����� ��ġ
	D3DXVECTOR2			m_objectPos;					// �������� ���̴� ��ġ (Ŀ���� �� �κ�)

	float				m_cursorMoveMaxSpeed;
	float				m_cursorMoveSpeed;

	PlaceableObject*	m_objectToPlace;				// ���� ������ �ϴ� ������Ʈ
	bool				m_isFlipped;
	bool				m_placed;						// ������Ʈ�� ���Ҵ°�?

	// �� ����
	int					m_paperWidth;
	int					m_paperHeight;
	float				m_cellSize;
	int					m_zeroHeightPoint, m_zeroWidthPoint;	// ����ĭ�� 0,0 (�� ���� �Ʒ� �κ�) ��ġ
private:
	void MoveCursor();
	pair<int, int> PosToIndex(D3DXVECTOR2 pos);
	D3DXVECTOR2 IndexToPos(pair<int, int> index);
public:
	PlayerCursor();
	~PlayerCursor();
	void ResetCursor(D3DXVECTOR2 pos);

	void Init(Sprite* cursorDefaultImg, Sprite* cursorOutOfBoundsImg);
	bool Update(vector<PlaceableObject*>& objList);
	void Render();
	void Release();

	void SetLeftMoveKey(int key) { m_leftMoveKey = key; }
	void SetRightMoveKey(int key) { m_rightMoveKey = key; }
	void SetUpMoveKey(int key) { m_upMoveKey = key; }
	void SetDownMoveKey(int key) { m_downMoveKey = key; }
	void SetSelectKey(int key) { m_selectKey = key; }
	void SetFlipKey(int key) { m_flipKey = key; }

	void SetCursorPosition(D3DXVECTOR2 pos);
	void SetObjectToPlace(PlaceableObject* obj) { m_objectToPlace = obj; }
	void SetFlipVal(bool val) { m_isFlipped = val; }
	bool HasPlacedObject() { return m_placed; }
};

