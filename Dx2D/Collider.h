#pragma once

class Player;
class Collider
{
protected:
	D3DXVECTOR2			m_center;
	Rect*				m_rect;			// AABB가 아닌 Collider의 경우 해당하는 도형에 외접하는 정사각형
	D3DXVECTOR2			m_halfSize;
	virtual void SetShapeHalfSize(D3DXVECTOR2 sz) PURE;
	virtual void SetShapeCenter(D3DXVECTOR2 c) PURE;
public:
	Collider();
	~Collider();

	virtual bool pointInCollider(D3DXVECTOR2 point) PURE;		// 픽셀충돌 검사용
	virtual void RenderCollider() PURE;
	void SetHalfSize(D3DXVECTOR2 sz);
	void SetCenter(D3DXVECTOR2 c);
	void Render()
	{
		if (g_pKeyManager->IsToggleKey('D'))
		{
			RenderCollider();
		}
	}

	// 사각형 사이즈 및 중심위치 getter/setter
	D3DXVECTOR2 GetHalfSize() { return m_halfSize; }
	D3DXVECTOR2 GetCenter() { return m_center; }
	void SetRectHalfSize(D3DXVECTOR2 sz) { m_halfSize = sz; m_rect->SetSize({ m_halfSize.x*2.0f, m_halfSize.y*2.0f }); }

	// 사각형의 네 개 꼭짓점 반환
	D3DXVECTOR2 GetLeftBottomPoint() { return m_center - m_halfSize; }
	D3DXVECTOR2 GetRightBottomPoint() { return { m_center.x + m_halfSize.x,  m_center.y - m_halfSize.y }; }
	D3DXVECTOR2 GetLeftTopPoint() { return { m_center.x - m_halfSize.x,  m_center.y + m_halfSize.y };}
	D3DXVECTOR2 GetRightTopPoint() { return m_center + m_halfSize; }
};

