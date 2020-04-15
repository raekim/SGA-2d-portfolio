#include "stdafx.h"
#include "SimplePlatform.h"
#include "Player.h"
#include "Map.h"

SimplePlatform::SimplePlatform(D3DXVECTOR2 AABBHalfSize, D3DXVECTOR2 pos)
{
	m_collider = new AABB;
	m_collider->SetHalfSize(AABBHalfSize);
	m_sprite = NULL;
	m_position = pos;
}

SimplePlatform::SimplePlatform(Platform_Type type)
{
	m_platformType = type;
	m_positionOffset = { 0,0 };
	m_collider = new AABB;
	switch (type)
	{
	case Platform_Type::SHORT_VERTICAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 6, 0);
		m_sprite->SetSize({ 0.7f, 0.7 });
		m_sprite->SetRotation({ 0, 0, D3DX_PI/2 });
		m_collider->SetHalfSize({ 15,60 });
		m_positionOffset = { 0, 36 };
		break;
	case Platform_Type::SHORT_HORIZONTAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 6, 0);
		m_sprite->SetSize({ 0.7f, 0.7 });
		m_collider->SetHalfSize({ 60,15 });
		m_positionOffset = { 35, 10 };
		break;
	case Platform_Type::MID_VERTICAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 3, 15);
		m_sprite->SetSize({ 0.7f, 0.7f });
		m_collider->SetHalfSize({ 23,91 });
		m_positionOffset = { 0, 6 };
		break;
	case Platform_Type::MID_HORIZONTAL:
		m_sprite = new Sprite(L"Object-Sheet-1", 6, 3, 15);
		m_sprite->SetSize({ 0.7f, 0.7f });
		m_sprite->SetRotation({ 0, 0, D3DX_PI / 2 });
		m_collider->SetHalfSize({ 91,23 });
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

void SimplePlatform::Update(vector<vector<PlaceableObject*>>& objList)
{
	m_collider->SetCenter(m_position + m_positionOffset);

	if (m_sprite)
	{
		m_sprite->SetPosition(m_position + m_positionOffset);
		m_sprite->Update();
	}

	PlaceableObject::RegisterObjectCollider(m_collider, objList);
}

void SimplePlatform::Render()
{
	if (m_sprite)
	{
		m_sprite->Render();
	}
	m_collider->Render();
}

void SimplePlatform::Release()
{
	SAFE_DELETE(m_sprite);
}

bool SimplePlatform::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	if (m_collider->pointInCollider(pos))
	{
		switch (dir)
		{
		case collisionCheckDir::BOTTOM:
			if (player->m_speed.y < 0.0f)
			{
				player->SetPositionY(((AABB*)m_collider)->GetAABBTop() + player->GetAABBHalfSize().y);
				player->m_speed.y = 0.0f;
			}
			break;
		case collisionCheckDir::CEILING:
			if (player->m_speed.y > 0.0f)
			{
				player->m_speed.y = 0.0f;
				player->SetPositionY(((AABB*)m_collider)->GetAABBBottom() - player->GetAABBHalfSize().y);
			}
			break;
		case collisionCheckDir::LEFT_WALL:
			if (player->m_speed.x < 0.0f)
			{
				player->SetPositionX(((AABB*)m_collider)->GetAABBRight() + player->GetAABBHalfSize().x);
				player->m_speed.x = 0.0f;
			}
			break;
		case collisionCheckDir::RIGHT_WALL:
			if (player->m_speed.x > 0.0f)
			{
				player->m_speed.x = 0.0f;
				player->SetPositionX(((AABB*)m_collider)->GetAABBLeft() - player->GetAABBHalfSize().x);
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

void SimplePlatform::SetPreviewImageColor(D3DXCOLOR color)
{
	m_sprite->SetColor(color);
}

bool SimplePlatform::CanPlaceObject(int h, int w, Map * map)
{
	bool res = false;

	// 비어있지 않은 칸은 true로 표현된다
	// 검사하는 칸들 중 하나라도 비어있지 않은 칸이 있었다면 res는 true가 될 것
	switch (m_platformType)
	{
	case Platform_Type::SHORT_VERTICAL:
		res |= map->GetCellStatus(h, w);
		res |= map->GetCellStatus(h + 1, w);
		break;
	case Platform_Type::SHORT_HORIZONTAL:
		res |= map->GetCellStatus(h, w);
		res |= map->GetCellStatus(h, w + 1);
		break;
	case Platform_Type::MID_VERTICAL:
		res |= map->GetCellStatus(h, w);
		res |= map->GetCellStatus(h + 1, w);
		res |= map->GetCellStatus(h - 1, w);
		break;
	case Platform_Type::MID_HORIZONTAL:
		res |= map->GetCellStatus(h, w + 1);
		res |= map->GetCellStatus(h, w - 1);
		res |= map->GetCellStatus(h, w);
		break;
	default:
		return false;
	}

	return !res;
}

void SimplePlatform::PlaceObject(int h, int w, Map * map)
{
	switch (m_platformType)
	{
	case Platform_Type::SHORT_VERTICAL:
		map->SetCellStatus(h, w, true);
		map->SetCellStatus(h + 1, w, true);
		break;
	case Platform_Type::SHORT_HORIZONTAL:
		map->SetCellStatus(h, w, true);
		map->SetCellStatus(h, w + 1, true);
		break;
	case Platform_Type::MID_VERTICAL:
		map->SetCellStatus(h + 1, w, true);
		map->SetCellStatus(h, w, true);
		map->SetCellStatus(h - 1, w, true);
		break;
	case Platform_Type::MID_HORIZONTAL:
		map->SetCellStatus(h, w + 1, true);
		map->SetCellStatus(h, w - 1, true);
		map->SetCellStatus(h, w, true);
		break;
	}
}
