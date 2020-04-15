#pragma once
#include "AABB.h"
#include "PlaceableObject.h"
#include "CircleCollider.h"
#include "Ball.h"

class BallShooter : public PlaceableObject
{
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	list<Ball*>				m_enabledBalls;				// Ȱ��ȭ�Ǿ� ������Ʈ�� ���� ����� Ball��
	list<Ball*>				m_disabledBalls;			// ��Ȱ��ȭ�Ǿ��ִ� ������Ʈ Ǯ Ball
	D3DXVECTOR2				m_shootStartSpeed;			// ���� �߻� ���ǵ�
	D3DXVECTOR2				m_shootStartPoint;			// �߻� ���� ����
	float					m_shootDelay;				// ���� �߻� �ҿ�ð�
	float					m_shootDelayCount;			// ���� �߻縦 ���� ī��Ʈ�ϴ� �ð�

	Sprite*					m_machineSprite;

	D3DXVECTOR2				m_ballOffset;				// �� �̹��� offset
	D3DXVECTOR2				m_ballRotationOffest;		// �� ȸ�� �߽��� offset
	D3DXVECTOR2				m_machineOffset;

public:
	BallShooter();
	~BallShooter();

	virtual void Init() override;
	virtual void Update(vector<vector<PlaceableObject*>>& objList) override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	virtual void RenderPreviewImage() override;

	virtual void SetPreviewImageColor(D3DXCOLOR color) override;
	virtual bool CanPlaceObject(int h, int w, Map* map) override;
	virtual void PlaceObject(int h, int w, Map* map) override;
};

