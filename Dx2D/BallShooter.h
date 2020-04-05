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
		float					m_xSpeedBound; // 발사된 공의 x 스피드의 절대값이 점점 감소하다가 이 밑으로는 감소하지 않는 값
		bool					m_isFlipped;

		Ball(bool flipped);
		void Update();
		void Render();

		virtual void Destory() override;					// 캐릭터 또는 오브젝트와 충돌
		virtual bool Collide(void* other) override;			// 다른 오브젝트와의 충돌 감지
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
	Sprite*					m_ballSprite;
	Sprite*					m_machineSprite;

	bool					m_isFlipped;				// 좌/우 반전 여부
	D3DXVECTOR2				m_ballOffset;				// 공 이미지 offset
	D3DXVECTOR2				m_ballRotationOffest;		// 공 회전 중심점 offset

public:
	BallShooter(D3DXVECTOR2 pos, bool flipped);
	~BallShooter();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
};

