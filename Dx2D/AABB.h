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
		bool collideTop, collideBottom, collideLeft, collideRight;	// 상하좌우 중 충돌이 일어난 side(두 개 이상일 수 있음) 체크
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

	// AABB의 꼭짓점 반환
	D3DXVECTOR2 GetLeftBottomPoint() { return m_center - m_halfSize; }
	D3DXVECTOR2 GetRightBottomPoint() { return { m_center.x + m_halfSize.x,  m_center.y - m_halfSize.y }; }

	// AABB의 상,하,좌,우 지점 반환
	float GetAABBTop() { return m_center.y + m_halfSize.y;}		// 타일의 위 y좌표
	float GetAABBBottom() { return m_center.y - m_halfSize.y; }	// 타일의 아래 y좌표
	float GetAABBLeft() { return m_center.x - m_halfSize.x; }		// 타일의 왼쪽 x좌표
	float GetAABBRight() { return m_center.x + m_halfSize.x; }		// 타일의 오른쪽 x좌표

	bool pointInAABB(D3DXVECTOR2 p);

	void Init();
	void Render();
	void Release();
};

