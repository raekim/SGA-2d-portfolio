// Axis Aligned Bounding Box (AABB)
#include "Collider.h"
#pragma once
class AABB : public Collider
{
public:
	struct collisionData
	{
		bool collideTop, collideBottom, collideLeft, collideRight;	// 상하좌우 중 충돌이 일어난 side(두 개 이상일 수 있음) 체크
	};
	collisionData	m_collisionData;

public:
	AABB();
	~AABB();

	bool CollideWithAABB(AABB* other);

	// AABB의 상,하,좌,우 모서리 반환
	float GetAABBTop() { return m_center.y + m_halfSize.y;}		// 타일의 위 y좌표
	float GetAABBBottom() { return m_center.y - m_halfSize.y; }	// 타일의 아래 y좌표
	float GetAABBLeft() { return m_center.x - m_halfSize.x; }		// 타일의 왼쪽 x좌표
	float GetAABBRight() { return m_center.x + m_halfSize.x; }		// 타일의 오른쪽 x좌표

	virtual void SetShapeHalfSize(D3DXVECTOR2 sz) override {};
	virtual void SetShapeCenter(D3DXVECTOR2 c) override {};
	virtual bool pointInCollider(D3DXVECTOR2 point) override;
	virtual void RenderCollider() override;
};

