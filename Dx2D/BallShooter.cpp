#include "stdafx.h"
#include "BallShooter.h"

float const BallShooter::Ball::m_minXSpeed = 400.0f;
BallShooter::BallShooter(D3DXVECTOR2 pos) : m_position(pos)
{
	m_shootStartPoint = { pos.x + 20.0f, pos.y };
	m_shootDelay = 3.5f;
	m_shootStartSpeed = { 700.f, 600.0f };

	for(int i=0; i<10; ++i)
		m_disabledBalls.emplace_back(new Ball());
}


BallShooter::~BallShooter()
{
}

void BallShooter::Init()
{
}

void BallShooter::Update()
{
	if (m_shootDelayCount >= m_shootDelay)
	{
		m_shootDelayCount = 0.0f;

		// shoot ball
		if (m_disabledBalls.size() <= 0)
		{
			m_disabledBalls.emplace_back(new Ball());
		}
		Ball* pBall = m_disabledBalls.front(); m_disabledBalls.pop_front();
		pBall->m_position = m_shootStartPoint;
		pBall->m_speed = m_shootStartSpeed;
		m_enabledBalls.push_back(pBall);
	}

	m_shootDelayCount += g_pTimeManager->GetDeltaTime();

	// 활성화 된 Ball들 업데이트
	for (auto it = m_enabledBalls.begin(); it != m_enabledBalls.end(); ++it)
	{
		Ball* pBall = *(it);
		if (pBall->m_position.x < 0 || pBall->m_position.x > GAMESCREEN_X ||
			pBall->m_position.y < 0 || pBall->m_position.y > GAMESCREEN_Y)
		{
			m_disabledBalls.push_back(m_disabledBalls.front());
			m_enabledBalls.erase(it);
			break;
		}
		pBall->Update();
	}
}

void BallShooter::Render()
{
	// 활성화 된 Ball들 렌더
	for (auto pBall : m_enabledBalls)
	{
		pBall->Render();
	}
}

void BallShooter::Release()
{
}

bool BallShooter::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	return false;
}
