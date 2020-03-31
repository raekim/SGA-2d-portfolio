#pragma once
#include "AABB.h"
#include "MovingObject.h"
class honeyPlatform : public MovingObject
{
	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	D3DXVECTOR2				m_AABBOffset;

	// �� �������� ������ �ӵ��� �Դٰ��� �Ѵ�
	D3DXVECTOR2				m_movingStartPoint;
	D3DXVECTOR2				m_movingEndPoint;
	float					m_moveSecond;		// �� ���������� �ٸ� ���������� ����� �̵��ϴ� �� �ɸ��� �ð� (�� ����)
	float					m_movingDelta;		// ���� ���� �������� ���� ��
public:
	honeyPlatform();
	~honeyPlatform();

	void Init();
	void Update();
	void Render();
	void Release();
	AABB* GetAABB() { return m_AABB; }
};

