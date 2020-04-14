#pragma once
#include "AABB.h"
#include "PlaceableObject.h""
class honeyPlatform : public PlaceableObject
{
	D3DXVECTOR2				m_cratePosition;
	D3DXVECTOR2				m_crateOffset;
	D3DXVECTOR2				m_midPosition;		// ��� �̵��� �� ������ ���� ��ġ
	D3DXVECTOR2				m_oldPosition;
	D3DXVECTOR2				m_moveDelta;
	D3DXVECTOR3				m_rotation;
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
	void Update(vector<vector<PlaceableObject*>>& objList);
	void Render();
	void Release();

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	virtual void RenderPreviewImage() override;

	virtual bool CanPlaceObject(int h, int w, Map* map) override;
	virtual void PlaceObject(int h, int w, Map* map) override;
	virtual void SetPreviewImageColor(D3DXCOLOR color) override;
};


