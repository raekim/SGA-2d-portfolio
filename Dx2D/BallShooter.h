#pragma once
#include "AABB.h"
#include "PlaceableObject.h"
#include "Projectile.h"

class BallShooter : public PlaceableObject
{
	struct Ball : public Projectile
	{
		Circle					m_circle;
		D3DXVECTOR2				m_speed;
		D3DXVECTOR2				m_position;
		float					m_xSpeedBound; // �߻�� ���� x ���ǵ��� ���밪�� ���� �����ϴٰ� �� �����δ� �������� �ʴ� ��
		bool					m_isFlipped;

		Ball(bool flipped);
		void Update();
		void Render();

		virtual void Destory() override;					// ĳ���� �Ǵ� ������Ʈ�� �浹
		virtual bool Collide(void* other) override;			// �ٸ� ������Ʈ���� �浹 ����
	};

	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	list<Ball*>				m_enabledBalls;				// Ȱ��ȭ�Ǿ� ������Ʈ�� ���� ����� Ball��
	list<Ball*>				m_disabledBalls;			// ��Ȱ��ȭ�Ǿ��ִ� ������Ʈ Ǯ Ball
	D3DXVECTOR2				m_shootStartSpeed;			// ���� �߻� ���ǵ�
	D3DXVECTOR2				m_shootStartPoint;			// �߻� ���� ����
	float					m_shootDelay;				// ���� �߻� �ҿ�ð�
	float					m_shootDelayCount;			// ���� �߻縦 ���� ī��Ʈ�ϴ� �ð�

	Circle*					m_tempBall;
	Sprite*					m_ballSprite;
	Sprite*					m_machineSprite;

	bool					m_isFlipped;				// ��/�� ���� ����
	D3DXVECTOR2				m_ballOffset;				// �� �̹��� offset
	D3DXVECTOR2				m_ballRotationOffest;		// �� ȸ�� �߽��� offset

public:
	BallShooter(D3DXVECTOR2 pos, bool flipped);
	~BallShooter();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
};

