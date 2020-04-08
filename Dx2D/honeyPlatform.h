#pragma once
#include "AABB.h"
#include "PlaceableObject.h""
class honeyPlatform : public PlaceableObject
{
	D3DXVECTOR2				m_cratePosition;
	D3DXVECTOR2				m_midPosition;		// ��� �̵��� �� ������ ���� ��ġ
	D3DXVECTOR2				m_oldPosition;
	D3DXVECTOR2				m_moveDelta;
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	D3DXVECTOR2				m_AABBOffset;
	Sprite*					m_crateSprite;		// ��� �̹���
	Sprite*					m_barSprite;		// ����� �Ŵ޷��� �����̴� �� �̹���

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

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	virtual void RenderPreviewImage() override;
};


