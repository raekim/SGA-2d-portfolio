// Axis Aligned Bounding Box (AABB)

#pragma once
class AABB 
{
	D3DXVECTOR2		m_center;
	D3DXVECTOR2		m_halfSize;
	Rect*			m_rect;
	bool			m_draw;
	
public:
	struct collisionData
	{
		bool collideTop, collideBottom, collideLeft, collideRight;	// �����¿� �� �浹�� �Ͼ side(�� �� �̻��� �� ����) üũ
	};
	collisionData	m_collisionData;

public:
	AABB(D3DXVECTOR2 halfSize);
	~AABB();

	bool Collide(AABB* other);
	void SetCenter(D3DXVECTOR2 c);
	void SetHalfSize(D3DXVECTOR2 sz) { m_halfSize = sz; }
	void SetDraw(bool b) { m_draw = b; }
	D3DXVECTOR2 GetHalfSize() { return m_halfSize; }
	D3DXVECTOR2 GetCenter() { return m_center; }

	// AABB�� ������ ��ȯ
	D3DXVECTOR2 GetLeftBottomPoint() { return m_center - m_halfSize; }
	D3DXVECTOR2 GetRightBottomPoint() { return { m_center.x + m_halfSize.x,  m_center.y - m_halfSize.y }; }

	// AABB�� ��,��,��,�� ���� ��ȯ
	float GetAABBTop() { return m_center.y + m_halfSize.y;}		// Ÿ���� �� y��ǥ
	float GetAABBBottom() { return m_center.y - m_halfSize.y; }	// Ÿ���� �Ʒ� y��ǥ
	float GetAABBLeft() { return m_center.x - m_halfSize.x; }		// Ÿ���� ���� x��ǥ
	float GetAABBRight() { return m_center.x + m_halfSize.x; }		// Ÿ���� ������ x��ǥ

	bool pointInAABB(D3DXVECTOR2 p);

	void Init();
	void Render();
	void Release();
};

