#pragma once
#include "AABB.h"
#include "PlaceableObject.h"

class BallShooter : public PlaceableObject
{
	struct Ball
	{
		Circle					m_circle;
		D3DXVECTOR2				m_speed;
		D3DXVECTOR2				m_position;
		static float const		m_minXSpeed; // �߻�� ���� x ���ǵ尡 ���� �����ϴٰ� �� �����δ� �������� �ʴ� ��

		Ball()
		{
			m_circle.SetRadius(30.0f);
			m_circle.SetDraw(true);
			m_speed = {0.0f, 0.0f};
		}

		void Update()
		{
			m_position += m_speed * g_pTimeManager->GetDeltaTime();
			m_speed.x -= 200.0f * g_pTimeManager->GetDeltaTime();
			m_speed.x = max(m_speed.x, m_minXSpeed);
			m_speed.y -= GRAVITY * g_pTimeManager->GetDeltaTime();
			m_circle.SetPosition(m_position);
			m_circle.Update();
		}

		void Render()
		{
			m_circle.Render();
		}
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
public:
	BallShooter(D3DXVECTOR2 pos);
	~BallShooter();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
};

