#pragma once

class PlaceableObject;
class PlayerCursor
{	
	int					m_selectKey, m_leftMoveKey, m_rightMoveKey, m_upMoveKey, m_downMoveKey, m_flipKey; // 컨트롤 정보
	Sprite*				m_cursorDefaultImage;			// 커서 이미지
	Sprite*				m_cursorOutOfBoundsImage;		// 아이템을 놓지 못하는 상태의 커서 이미지
	D3DXVECTOR2			m_cursorPos;					// 커서 이미지의 위치
	D3DXVECTOR2			m_objectPos;					// 아이템이 놓이는 위치 (커서의 끝 부분)

	float				m_cursorMoveMaxSpeed;
	float				m_cursorMoveSpeed;

	PlaceableObject*	m_objectToPlace;				// 현재 놓고자 하는 오브젝트
	bool				m_isFlipped;
	bool				m_placed;						// 오브젝트를 놓았는가?

	// 맵 정보
	int					m_paperWidth;
	int					m_paperHeight;
	float				m_cellSize;
	int					m_zeroHeightPoint, m_zeroWidthPoint;	// 격자칸의 0,0 (맨 왼쪽 아래 부분) 위치
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

