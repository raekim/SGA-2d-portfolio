#include "stdafx.h"
#include "AABB.h"



AABB::AABB()
{
}


AABB::~AABB()
{
}

bool AABB::CollideWithAABB(AABB* other)
{
	if (fabs(m_center.x - other->m_center.x) > (m_halfSize.x + other->m_halfSize.x)) return false; // x축 검사
	if (fabs(m_center.y - other->m_center.y) > (m_halfSize.y + other->m_halfSize.y)) return false; // y축 검사
	return true;
}

bool AABB::pointInCollider(D3DXVECTOR2 point)
{
	if (point.x < m_center.x - m_halfSize.x || m_center.x + m_halfSize.x < point.x) return false; // x축 검사
	if (point.y < m_center.y - m_halfSize.y || m_center.y + m_halfSize.y < point.y) return false; // y축 검사
	return true;
}

void AABB::RenderCollider()
{
	m_rect->Render();
}
