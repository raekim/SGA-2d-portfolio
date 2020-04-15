#pragma once

class PlaceableObject;
class Map;
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
	bool				m_canPlaceObjectOnCurPos;		// ���� ��ġ�� ������ �ϴ� ������Ʈ�� ���� �� �ִ°�?

	Map*				m_map;
private:
	void MoveCursor();
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
	void SetMap(Map* map) { m_map = map; }

	void SetCursorPosition(D3DXVECTOR2 pos);
	void SetObjectToPlace(PlaceableObject* obj) { m_objectToPlace = obj; }
	void SetFlipVal(bool val) { m_isFlipped = val; }
	bool HasPlacedObject() { return m_placed; }
};

