#pragma once
#include "AABB.h"
#include "PlaceableObject.h"
class BallShooter : public PlaceableObject
{
	struct Ball
	{
		Circle			m_circle;
		bool			m_enabled;
		D3DXVECTOR2		m_speed;

		Ball()
		{
			m_circle.SetRadius(10.0f);
			m_enabled = false;
			m_speed = {0.0f, 0.0f};
		}
	};

	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	queue<Ball*>			m_balls;
	D3DXVECTOR2				m_shootStartSpeed;			// ���� �߻� ���ǵ�
	D3DXVECTOR2				m_shootStartPoint;			// �߻� ���� ����
	float					m_minXSpeed;				// �߻�� ���� x ���ǵ尡 ���� �����ϴٰ� �� �����δ� �������� �ʴ� ��
	float					m_shootDelay;				// ���� �߻� �ҿ�ð�
	float					m_shootDelayCount;			// ���� �߻縦 ���� ī��Ʈ�ϴ� �ð�

	Circle*					m_tempBall;
public:
	BallShooter(D3DXVECTOR2 pos);
	~BallShooter();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
};

