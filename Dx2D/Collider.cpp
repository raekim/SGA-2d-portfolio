#include "stdafx.h"
#include "Collider.h"


Collider::Collider()
{
	m_rect = new Rect;
	m_rect->Init();
}

Collider::~Collider()
{
}

void Collider::SetHalfSize(D3DXVECTOR2 sz)
{
	m_halfSize = sz;
	m_rect->SetSize({ sz.x * 2, sz.y * 2 });
	m_rect->Update();

	SetShapeHalfSize(sz);
}

void Collider::SetCenter(D3DXVECTOR2 c)
{
	m_center = c;
	m_rect->SetPosition(c);
	m_rect->Update();

	SetShapeCenter(c);
}

