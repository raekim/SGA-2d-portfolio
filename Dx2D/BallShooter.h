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
	D3DXVECTOR2				m_shootStartSpeed;			// 최초 발사 스피드
	D3DXVECTOR2				m_shootStartPoint;			// 발사 시작 지점
	float					m_minXSpeed;				// 발사된 공의 x 스피드가 점점 감소하다가 이 밑으로는 감소하지 않는 값
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

