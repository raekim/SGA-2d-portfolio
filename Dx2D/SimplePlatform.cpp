#include "stdafx.h"
#include "SimplePlatform.h"
#include "Player.h"

SimplePlatform::SimplePlatform(D3DXVECTOR2 AABBHalfSize, D3DXVECTOR2 pos)
{
	m_AABB = new AABB;
	m_AABB->SetHalfSize(AABBHalfSize);
	m_sprite = NULL;
	m_position = pos;
}

SimplePlatform::SimplePlatform(Platform_Type type)
{
	m_positionOffset = { 0,0 };
	m_AABB = new AABB;
	switch (type)
	{
	case Platform_Type::SHORT_VERTICAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 6, 0);
		m_sprite->SetSize({ 0.7f, 0.7 });
		m_sprite->SetRotation({ 0, 0, D3DX_PI/2 });
		m_AABB->SetHalfSize({ 15,60 });
		m_positionOffset = { 0, 36 };
		break;
	case Platform_Type::SHORT_HORIZONTAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 6, 0);
		m_sprite->SetSize({ 0.7f, 0.7 });
		m_AABB->SetHalfSize({ 60,15 });
		m_positionOffset = { 35, 10 };
		break;
	case Platform_Type::MID_VERTICAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 3, 15);
		m_sprite->SetSize({ 0.7f, 0.7f });
		m_AABB->SetHalfSize({ 23,91 });
		m_positionOffset = { 0, 6 };
		break;
	case Platform_Type::MID_HORIZONTAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 3, 15);
		m_sprite->SetSize({ 0.7f, 0.7f });
		m_sprite->SetRotation({ 0, 0, D3DX_PI / 2 });
		m_AABB->SetHalfSize({ 91,23 });
		m_positionOffset = { 5, 8 };
		break;
	}
}


SimplePlatform::~SimplePlatform()
{
	this->Release();
}

void SimplePlatform::Init()
{
	m_rotation = { 0.0f, 0.0f, 0.0f };
}

void SimplePlatform::Update(vector<Collider*>& colliders)
{
	m_AABB->SetCenter(m_position + m_positionOffset);
	
	if (m_sprite)
	{
		m_sprite->SetPosition(m_position + m_positionOffset);
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
	if (m_AABB->pointInCollider(pos))
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

void SimplePlatform::RenderPreviewImage()
{
	if (m_sprite)
	{
		m_sprite->SetPosition(m_position + m_positionOffset);
		m_sprite->Update();
		m_sprite->Render();
	}
}
