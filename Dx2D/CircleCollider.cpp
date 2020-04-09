#include "stdafx.h"
#include "CircleCollider.h"


CircleCollider::CircleCollider()
{
	m_circle = new Circle;
	m_circle->Init();
}


CircleCollider::~CircleCollider()
{
}

bool CircleCollider::pointInCollider(D3DXVECTOR2 point)
{
	return PointInCircle(m_center, m_halfSize.x, point);
}

void CircleCollider::RenderCollider()
{
	m_circle->Render();
}

void CircleCollider::SetShapeHalfSize(D3DXVECTOR2 sz)
{
	m_circle->SetRadius(sz.x);
	m_circle->Update();
}

void CircleCollider::SetShapeCenter(D3DXVECTOR2 c)
{
	m_circle->SetPosition(c);
	m_circle->Update();
}

Circle * CircleCollider::GetCircle()
{
	return m_circle;
}
