#include "stdafx.h"
#include "AABB.h"



AABB::AABB(D3DXVECTOR2 halfSize): m_halfSize(halfSize)
{
}


AABB::~AABB()
{
}

bool AABB::Collide(AABB* other)
{
	if (fabs(m_center.x - other->m_center.x) > (m_halfSize.x + other->m_halfSize.x)) return false; // x�� �˻�
	if (fabs(m_center.y - other->m_center.y) > (m_halfSize.y + other->m_halfSize.y)) return false; // y�� �˻�
	
	return true; // x��� y�� �� �� ��ġ�� �浹
}

void AABB::SetCenter(D3DXVECTOR2 c)
{
	m_center = c;
	m_rect->SetPosition(m_center);
	m_rect->Update();
}

void AABB::Init()
{
	m_rect = new Rect();
	m_rect->Init();
	m_rect->SetSize({ m_halfSize.x*2.0f, m_halfSize.y*2.0f });
	m_rect->SetDraw(true);
	m_draw = true;
}

void AABB::Render()
{
	if (m_draw)
	{
		m_rect->Render();
	}
}

void AABB::Release()
{
	SAFE_DELETE(m_rect);
}
