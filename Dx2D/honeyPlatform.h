#pragma once
#include "AABB.h"
#include "MovingObject.h"
class honeyPlatform : public MovingObject
{
	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	D3DXVECTOR2				m_AABBOffset;

	// 두 기준점을 일정한 속도로 왔다갔다 한다
	D3DXVECTOR2				m_movingStartPoint;
	D3DXVECTOR2				m_movingEndPoint;
	float					m_moveSecond;		// 한 기준점에서 다른 기준점으로 블록이 이동하는 데 걸리는 시간 (초 단위)
	float					m_movingDelta;		// 선형 보간 기준으로 쓰일 값
public:
	honeyPlatform();
	~honeyPlatform();

	void Init();
	void Update();
	void Render();
	void Release();
	AABB* GetAABB() { return m_AABB; }
};

