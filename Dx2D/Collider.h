#pragma once

class Player;
class Collider
{
protected:
	D3DXVECTOR2			m_center;
	Rect*				m_rect;			// AABB�� �ƴ� Collider�� ��� �ش��ϴ� ������ �����ϴ� ���簢��
	D3DXVECTOR2			m_halfSize;
	virtual void SetShapeHalfSize(D3DXVECTOR2 sz) PURE;
	virtual void SetShapeCenter(D3DXVECTOR2 c) PURE;
public:
	Collider();
	~Collider();

	virtual bool pointInCollider(D3DXVECTOR2 point) PURE;		// �ȼ��浹 �˻��
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

	// �簢�� ������ �� �߽���ġ getter/setter
	D3DXVECTOR2 GetHalfSize() { return m_halfSize; }
	D3DXVECTOR2 GetCenter() { return m_center; }
	void SetRectHalfSize(D3DXVECTOR2 sz) { m_halfSize = sz; m_rect->SetSize({ m_halfSize.x*2.0f, m_halfSize.y*2.0f }); }

	// �簢���� �� �� ������ ��ȯ
	D3DXVECTOR2 GetLeftBottomPoint() { return m_center - m_halfSize; }
	D3DXVECTOR2 GetRightBottomPoint() { return { m_center.x + m_halfSize.x,  m_center.y - m_halfSize.y }; }
	D3DXVECTOR2 GetLeftTopPoint() { return { m_center.x - m_halfSize.x,  m_center.y + m_halfSize.y };}
	D3DXVECTOR2 GetRightTopPoint() { return m_center + m_halfSize; }
};

