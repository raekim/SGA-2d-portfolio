#include "stdafx.h"
#include "BallShooter.h"


BallShooter::BallShooter(D3DXVECTOR2 pos) : m_position(pos)
{
	m_shootStartPoint = { pos.x + 20.0f, pos.y };
	m_shootDelay = 3.5f;

	for(int i=0; i<10; ++i)
		m_balls.push(new Ball());
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
		auto ball = m_balls.front();
		ball->m_enabled = true;
		ball->m_speed = 
	}

	m_shootDelayCount += g_pTimeManager->GetDeltaTime();
}

void BallShooter::Render()
{
}

void BallShooter::Release()
{
}

bool BallShooter::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	return false;
}
