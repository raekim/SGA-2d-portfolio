#pragma once
#include "AABB.h"
#include "PlaceableObject.h""
class honeyPlatform : public PlaceableObject
{
	D3DXVECTOR2				m_cratePosition;
	D3DXVECTOR2				m_midPosition;		// 블록 이동의 두 기준점 사이 위치
	D3DXVECTOR2				m_oldPosition;
	D3DXVECTOR2				m_moveDelta;
	D3DXVECTOR3				m_rotation;
	D3DXVECTOR2				m_AABBOffset;
	Sprite*					m_crateSprite;		// 블록 이미지
	Sprite*					m_barSprite;		// 블록이 매달려서 움직이는 선 이미지

	// 두 기준점을 일정한 속도로 왔다갔다 한다
	D3DXVECTOR2				m_movingStartPoint;
	D3DXVECTOR2				m_movingEndPoint;
	float					m_moveSecond;		// 한 기준점에서 다른 기준점으로 블록이 이동하는 데 걸리는 시간 (초 단위)
	float					m_movingDelta;		// 선형 보간 기준으로 쓰일 값
public:
	honeyPlatform();
	~honeyPlatform();

	void Init();
	void Update(vector<vector<PlaceableObject*>>& objList);
	void Render();
	void Release();

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	virtual void RenderPreviewImage() override;
};


