#include "stdafx.h"
#include "SimplePlatform.h"
#include "Player.h"

SimplePlatform::SimplePlatform(D3DXVECTOR2 AABBHalfSize, D3DXVECTOR2 pos)
{
	m_AABB = new AABB(AABBHalfSize);
	m_AABB->Init();
	m_position = pos;
}


SimplePlatform::~SimplePlatform()
{
}

void SimplePlatform::Init()
{
	m_rotation = { 0.0f, 0.0f, 0.0f };
}

void SimplePlatform::Update()
{
	m_AABB->SetCenter(m_position);
}

void SimplePlatform::Render()
{
	m_AABB->Render();
}

void SimplePlatform::Release()
{
}

bool SimplePlatform::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
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
