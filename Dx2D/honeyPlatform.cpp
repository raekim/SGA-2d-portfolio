#include "stdafx.h"
#include "honeyPlatform.h"
#include "Player.h"

honeyPlatform::honeyPlatform()
{
}


honeyPlatform::~honeyPlatform()
{
}

void honeyPlatform::Init()
{
	m_AABB = new AABB({ 40.0f, 40.0f });
	m_AABB->Init();

	m_oldPosition = m_position = { WINSIZEX*0.5f - 300.0f, WINSIZEY - 700.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };

	m_movingStartPoint = m_position - D3DXVECTOR2(200.0f, 200.0f);
	m_movingEndPoint = m_position + D3DXVECTOR2(200.0f, 200.0f);

	m_moveSecond = 2.5f;
	m_movingDelta = 0.0f;
}

void honeyPlatform::Update()
{
	// 두 기준점 m_movingStartPoint, m_movingEndPoint 사이를 선형 보간을 사용하여 움직인다
	m_position = LinearInterpolation(m_movingStartPoint, m_movingEndPoint, min(m_movingDelta / m_moveSecond, 1.0f));
	m_AABB->SetCenter(m_position);
	m_moveDelta = m_position - m_oldPosition;

	// 한 쪽 기준점에 도달하였으면 반대쪽 정점으로 이동 방향을 바꾼다
	if (m_movingDelta >= m_moveSecond + 0.1f)
	{
		m_movingDelta = 0.0f;
		m_oldPosition = m_position = m_movingEndPoint;
		swap(m_movingStartPoint, m_movingEndPoint);
	}
	
	m_oldPosition = m_position; 
	m_movingDelta += g_pTimeManager->GetDeltaTime();
}

void honeyPlatform::Render()
{
	m_AABB->Render();
}

void honeyPlatform::Release()
{
	m_AABB->Release();
}

bool honeyPlatform::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	if (m_AABB->pointInAABB(pos))
	{
		switch (dir)
		{
		case collisionCheckDir::BOTTOM:
			player->SetPositionY(m_AABB->GetAABBTop() + player->GetAABBHalfSize().y);
			if (player->m_speed.y < 0.0f) player->m_speed.y = 0.0f;
			player->m_position += m_moveDelta;
			break;
		case collisionCheckDir::CEILING:
			player->SetPositionY(m_AABB->GetAABBBottom() - player->GetAABBHalfSize().y);
			if (player->m_speed.y > 0.0f) player->m_speed.y = 0.0f;
			break;
		case collisionCheckDir::LEFT_WALL:
			player->SetPositionX(m_AABB->GetAABBRight() + player->GetAABBHalfSize().x);
			if (player->m_speed.x < 0.0f) player->m_speed.x = 0.0f;
			player->m_position += m_moveDelta;
			break;
		case collisionCheckDir::RIGHT_WALL:
			player->SetPositionX(m_AABB->GetAABBLeft() - player->GetAABBHalfSize().x);
			if (player->m_speed.x > 0.0f) player->m_speed.x = 0.0f;
			player->m_position += m_moveDelta;
			break;
		}
		return true;
	}
	return false;
}

void honeyPlatform::SetPosition(D3DXVECTOR2 pos)
{
	m_position = pos;
	m_movingStartPoint = m_position - D3DXVECTOR2(200.0f, 200.0f);
	m_movingEndPoint = m_position + D3DXVECTOR2(200.0f, 200.0f);
}
