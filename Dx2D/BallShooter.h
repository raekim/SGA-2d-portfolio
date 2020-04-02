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
		static float const		m_minXSpeed; // 발사된 공의 x 스피드가 점점 감소하다가 이 밑으로는 감소하지 않는 값

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
	list<Ball*>				m_enabledBalls;				// 활성화되어 업데이트와 렌더 대상인 Ball들
	list<Ball*>				m_disabledBalls;			// 비활성화되어있는 오브젝트 풀 Ball
	D3DXVECTOR2				m_shootStartSpeed;			// 최초 발사 스피드
	D3DXVECTOR2				m_shootStartPoint;			// 발사 시작 지점
	float					m_shootDelay;				// 연속 발사 소요시간
	float					m_shootDelayCount;			// 연속 발사를 위해 카운트하는 시간

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

