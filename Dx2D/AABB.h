// Axis Aligned Bounding Box (AABB)
#include "Collider.h"
#pragma once
class AABB : public Collider
{
public:
	struct collisionData
	{
		bool collideTop, collideBottom, collideLeft, collideRight;	// �����¿� �� �浹�� �Ͼ side(�� �� �̻��� �� ����) üũ
	};
	collisionData	m_collisionData;

public:
	AABB();
	~AABB();

	bool CollideWithAABB(AABB* other);

	// AABB�� ��,��,��,�� �𼭸� ��ȯ
	float GetAABBTop() { return m_center.y + m_halfSize.y;}		// Ÿ���� �� y��ǥ
	float GetAABBBottom() { return m_center.y - m_halfSize.y; }	// Ÿ���� �Ʒ� y��ǥ
	float GetAABBLeft() { return m_center.x - m_halfSize.x; }		// Ÿ���� ���� x��ǥ
	float GetAABBRight() { return m_center.x + m_halfSize.x; }		// Ÿ���� ������ x��ǥ

	virtual void SetShapeHalfSize(D3DXVECTOR2 sz) override {};
	virtual void SetShapeCenter(D3DXVECTOR2 c) override {};
	virtual bool pointInCollider(D3DXVECTOR2 point) override;
	virtual void RenderCollider() override;
};

