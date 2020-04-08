#pragma once

class PlaceableObject;
class PlayerCursor
{
	// ��Ʈ�� ����
	int					m_selectKey, m_leftMoveKey, m_rightMoveKey, m_upMoveKey, m_downMoveKey;
	Sprite*				m_cursorDefaultImage;			// Ŀ�� �̹���
	Sprite*				m_cursorOutOfBoundsImage;		// �������� ���� ���ϴ� ������ Ŀ�� �̹���
	D3DXVECTOR2			m_cursorPos;					// Ŀ�� �̹����� ��ġ
	D3DXVECTOR2			m_objectPos;					// �������� ���̴� ��ġ (Ŀ���� �� �κ�)

	float				m_cursorMoveMaxSpeed;
	float				m_cursorMoveSpeed;

	PlaceableObject*	m_objectToPlace;			// ���� ������ �ϴ� ������Ʈ

	// �� ����
	int					m_paperWidth;
	int					m_paperHeight;
	float				m_cellSize;
	int					m_zeroHeightPoint, m_zeroWidthPoint;	// ����ĭ�� 0,0 (�� ���� �Ʒ� �κ�) ��ġ
private:
	void MoveCursor();
public:
	PlayerCursor();
	~PlayerCursor();

	void Init(Sprite* cursorDefaultImg, Sprite* cursorOutOfBoundsImg);
	bool Update(vector<PlaceableObject*>& objList);
	void Render();
	void Release();

	void SetLeftMoveKey(int key) { m_leftMoveKey = key; }
	void SetRightMoveKey(int key) { m_rightMoveKey = key; }
	void SetUpMoveKey(int key) { m_upMoveKey = key; }
	void SetDownMoveKey(int key) { m_downMoveKey = key; }
	void SetSelectKey(int key) { m_selectKey = key; }

	void SetCursorPosition(D3DXVECTOR2 pos);
	void SetObjectToPlace(PlaceableObject* obj) { m_objectToPlace = obj; }
};

