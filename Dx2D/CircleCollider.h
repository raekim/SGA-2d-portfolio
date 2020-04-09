#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
	Circle* m_circle;
public:
	CircleCollider();
	~CircleCollider();

	virtual bool pointInCollider(D3DXVECTOR2 point) override;		// �ȼ��浹 �˻��
	virtual void RenderCollider() override;
	virtual void SetShapeHalfSize(D3DXVECTOR2 sz) override;
	virtual void SetShapeCenter(D3DXVECTOR2 c) override;
	Circle* GetCircle();
};

