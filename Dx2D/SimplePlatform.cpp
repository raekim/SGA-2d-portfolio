#include "stdafx.h"
#include "SimplePlatform.h"
#include "Player.h"

SimplePlatform::SimplePlatform(D3DXVECTOR2 AABBHalfSize, D3DXVECTOR2 pos)
{
	m_sprite = NULL;
	m_AABB = new AABB(AABBHalfSize);
	m_AABB->Init();
	m_position = pos;
}

SimplePlatform::SimplePlatform(Platform_Type type, D3DXVECTOR2 pos)
{
	switch (type)
	{
	case Platform_Type::SHORT_VERTICAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 6, 0);
		m_sprite->SetSize({ 0.7f, 0.7 });
		m_sprite->SetRotation({ 0, 0, D3DX_PI/2 });
		m_AABB = new AABB({ 15,60 });
		break;
	case Platform_Type::SHORT_HORIZONTAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 6, 0);
		m_sprite->SetSize({ 0.7f, 0.7 });
		m_AABB = new AABB({ 60,15 });
		break;
	case Platform_Type::MID_VERTICAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 3, 15);
		m_sprite->SetSize({ 0.7f, 0.7f });
		m_AABB = new AABB({ 23,91 });
		break;
	case Platform_Type::MID_HORIZONTAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 3, 15);
		m_sprite->SetSize({ 0.7f, 0.7f });
		m_sprite->SetRotation({ 0, 0, D3DX_PI / 2 });
		m_AABB = new AABB({ 91,23 });
		break;
	}
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
	
	if (m_sprite)
	{
		m_sprite->SetPosition(m_position);
		m_sprite->Update();
	}
}

void SimplePlatform::Render()
{
	if (m_sprite)
	{
		m_sprite->Render();
	}
	m_AABB->Render();
}

void SimplePlatform::Release()
{
	SAFE_DELETE(m_AABB);
	SAFE_DELETE(m_sprite);
}

bool SimplePlatform::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	if (m_AABB->pointInAABB(pos))
	{
		switch (dir)
		{
		case collisionCheckDir::BOTTOM:
			if (player->m_speed.y < 0.0f)
			{
				player->SetPositionY(m_AABB->GetAABBTop() + player->GetAABBHalfSize().y);
				player->m_speed.y = 0.0f;
			}
			break;
		case collisionCheckDir::CEILING:
			if (player->m_speed.y > 0.0f)
			{
				player->m_speed.y = 0.0f;
				player->SetPositionY(m_AABB->GetAABBBottom() - player->GetAABBHalfSize().y);
			}
			break;
		case collisionCheckDir::LEFT_WALL:
			if (player->m_speed.x < 0.0f)
			{
				player->SetPositionX(m_AABB->GetAABBRight() + player->GetAABBHalfSize().x);
				player->m_speed.x = 0.0f;
			}
			break;
		case collisionCheckDir::RIGHT_WALL:
			if (player->m_speed.x > 0.0f)
			{
				player->m_speed.x = 0.0f;
				player->SetPositionX(m_AABB->GetAABBLeft() - player->GetAABBHalfSize().x);
			}
			break;
		}
		return true;
	}
	return false;
}
