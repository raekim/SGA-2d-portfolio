#pragma once
#include "AABB.h"
#include "PlaceableObject.h""
class honeyPlatform : public PlaceableObject
{
	D3DXVECTOR2				m_oldPosition;
	D3DXVECTOR2				m_moveDelta;
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
	honeyPlatform(D3DXVECTOR2 pos);
	~honeyPlatform();

	void Init();
	void Update();
	void Render();
	void Release();

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	void SetPosition(D3DXVECTOR2 pos);
};

