#include "stdafx.h"
#include "BallShooter.h"
#include "Player.h"

float const BallShooter::Ball::m_minXSpeed = 400.0f;
BallShooter::BallShooter(D3DXVECTOR2 pos) : m_position(pos)
{
	m_AABB = new AABB({25.0f, 25.0f});
	m_AABB->Init();

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
		pBall->SetDestroyed(false);
		m_enabledBalls.push_back(pBall);
	}

	m_shootDelayCount += g_pTimeManager->GetDeltaTime();

	// 활성화 된 Ball들 업데이트
	for (auto it = m_enabledBalls.begin(); it != m_enabledBalls.end(); ++it)
	{
		Ball* pBall = *(it);
		if (pBall->m_position.x < 0 || pBall->m_position.x > GAMESCREEN_X ||
			pBall->m_position.y < 0 || pBall->m_position.y > GAMESCREEN_Y || pBall->IsDestroyed())
		{
			m_disabledBalls.push_back(pBall);
			m_enabledBalls.erase(it);
			break;
		}
		pBall->Update();
	}
	m_AABB->SetCenter(m_position);
}

void BallShooter::Render()
{
	// 활성화 된 Ball들 렌더
	for (auto pBall : m_enabledBalls)
	{
		pBall->Render();
	}
	m_AABB->Render();
}

void BallShooter::Release()
{
}

bool BallShooter::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	// 플레이어와 발사체가 충돌했다면 플레이어 사망
	for (auto it = m_enabledBalls.begin(); it != m_enabledBalls.end(); ++it)
	{
		Ball* pBall = *(it);
		if (CircleCollision(pBall->m_circle.GetPosition(), pBall->m_circle.GetRadius(),
			player->m_position, min(player->GetAABBHalfSize().x, player->GetAABBHalfSize().y)))
		{
			if (PointInCircle(pBall->m_circle.GetPosition(), pBall->m_circle.GetRadius(), pos))
			{
				pBall->Destory();
				m_disabledBalls.push_back(pBall);
				m_enabledBalls.erase(it);
				break;
			}
		}
	}

	// shooter 본체와 충돌
	if (m_AABB->pointInAABB(pos))
	{
		switch (dir)
		{
		case collisionCheckDir::BOTTOM:
			player->SetPositionY(m_AABB->GetAABBTop() + player->GetAABBHalfSize().y);
			if (player->m_speed.y < 0.0f) player->m_speed.y = 0.0f;
			break;
		case collisionCheckDir::CEILING:
			player->SetPositionY(m_AABB->GetAABBBottom() - player->GetAABBHalfSize().y);
			if (player->m_speed.y > 0.0f) player->m_speed.y = 0.0f;
			break;
		case collisionCheckDir::LEFT_WALL:
			player->SetPositionX(m_AABB->GetAABBRight() + player->GetAABBHalfSize().x);
			if (player->m_speed.x < 0.0f) player->m_speed.x = 0.0f;
			break;
		case collisionCheckDir::RIGHT_WALL:
			player->SetPositionX(m_AABB->GetAABBLeft() - player->GetAABBHalfSize().x);
			if (player->m_speed.x > 0.0f) player->m_speed.x = 0.0f;
			break;
		}
		return true;
	}
	return false;
}

BallShooter::Ball::Ball()
{
	m_circle.SetRadius(30.0f);
	m_circle.SetDraw(true);
	m_speed = { 0.0f, 0.0f };
	Projectile::SetDestroyed(true);
}

void BallShooter::Ball::Update()
{
	m_position += m_speed * g_pTimeManager->GetDeltaTime();
	m_speed.x -= 200.0f * g_pTimeManager->GetDeltaTime();
	m_speed.x = max(m_speed.x, m_minXSpeed);
	m_speed.y -= GRAVITY * g_pTimeManager->GetDeltaTime();
	m_circle.SetPosition(m_position);
	m_circle.Update();
}

void BallShooter::Ball::Render()
{
	m_circle.Render();
}

void BallShooter::Ball::Destory()
{
	Projectile::SetDestroyed(true);
}

bool BallShooter::Ball::Collide(void * other)
{
	return false;
}
