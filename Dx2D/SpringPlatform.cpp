#include "stdafx.h"
#include "SpringPlatform.h"
#include "Player.h"
#include "Map.h"

SpringPlatform::SpringPlatform()
{
	m_previewImage = new Sprite(L"springBoard-3", 1, 1, 0);
	m_positionOffset = { 0,30 };
}


SpringPlatform::~SpringPlatform()
{
}

void SpringPlatform::Init()
{
	m_AABB = new AABB;
	m_AABBSizeAnimation = new Animation<STATE>;
	m_animation = new Animation<STATE>;
	m_AABB->SetHalfSize({ 10,10 });

	Clip* clip;
	Sprite* sprite;

	// IDLE
	clip = new Clip;
	sprite = new Sprite(L"springBoard-3", 1, 1, 0);
	clip->AddFrame(sprite, 1 / 12.0f);
	m_AABBSizeAnimation->AddClip(STATE::Idle, clip);

	clip = new Clip;
	sprite = new Sprite(L"Object-Sheet-1", 6, 6, 18 + 3);
	clip->AddFrame(sprite, 1 / 12.0f);
	m_animation->AddClip(STATE::Idle, clip);

	// Pushed
	clip = new Clip;// (PlayMode::Once);
	for (int i = 3; i >= 0; --i)
	{
		sprite = new Sprite(L"springBoard-" + to_wstring(i), 1, 1, 0);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_AABBSizeAnimation->AddClip(STATE::Pushed, clip);

	clip = new Clip(PlayMode::Once);
	for (int i = 3; i >= 0; --i)
	{
		sprite = new Sprite(L"Object-Sheet-1", 6, 6, 18 + i);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_animation->AddClip(STATE::Pushed, clip);

	// Springly
	clip = new Clip(PlayMode::Once);
	int idx[] = { 2,5,4,3,4,3,2,3,2 };
	for (int i = 0; i < 9; ++i)
	{
		sprite = new Sprite(L"springBoard-" + to_wstring(idx[i]), 1, 1, 0);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_AABBSizeAnimation->AddClip(STATE::Springly, clip);

	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 9; ++i)
	{
		sprite = new Sprite(L"Object-Sheet-1", 6, 6, 18 + idx[i]);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_animation->AddClip(STATE::Springly, clip);

	// Animation Init
	m_animation->SetScale(0.5f, 0.5f);
	m_AABBSizeAnimation->SetScale(0.5f, 0.5f);
	m_curState = STATE::Idle;
}

void SpringPlatform::Update(vector<vector<PlaceableObject*>>& objList)
{
	m_AABBSizeAnimation->Play(m_curState);
	m_AABBSizeAnimation->SetPosition(m_position + m_positionOffset);
	m_AABBSizeAnimation->Update();

	m_animation->Play(m_curState);
	m_animation->SetPosition(m_position + m_positionOffset);
	m_animation->Update();
	m_AABB->SetCenter({ m_position.x + m_positionOffset.x, m_position.y + m_positionOffset.y - (m_animation->GetWidth()*0.5f - m_AABBSizeAnimation->GetHeight()*0.5f) + 5 });
	m_AABB->SetHalfSize({ m_AABBSizeAnimation->GetWidth()*0.5f, m_AABBSizeAnimation->GetHeight()*0.5f });

	switch (m_curState)
	{
	case STATE::Springly:
		if (m_animation->IsDonePlaying(STATE::Springly))
		{
			m_curState = STATE::Idle;
		}
		break;
	}

	PlaceableObject::RegisterObjectCollider(m_AABB, objList);
}

void SpringPlatform::Render()
{
	m_AABB->Render();
	m_animation->Render();
}

void SpringPlatform::Release()
{
	SAFE_DELETE(m_AABB);
	SAFE_DELETE(m_animation);
	SAFE_DELETE(m_AABBSizeAnimation);
}

bool SpringPlatform::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	if (m_AABB->pointInCollider(pos))
	{
		switch (dir)
		{
		case collisionCheckDir::BOTTOM:
			if (player->m_speed.y < 0.0f)
			{
				player->m_speed.y = 0.0f;
				player->SetPositionY(m_AABB->GetAABBTop() + player->GetAABBHalfSize().y);
			}
			if (m_curState == STATE::Idle)
			{
				m_curState = STATE::Springly;
				player->SetPositionY(m_AABB->GetAABBTop() + player->GetAABBHalfSize().y + 15);
				player->m_speed.y = player->IsDead()? 600.0f : 1300.0f;
				player->Jump();
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
				player->m_speed.x = 0.0f;
				player->SetPositionX(m_AABB->GetAABBRight() + player->GetAABBHalfSize().x);
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

void SpringPlatform::RenderPreviewImage()
{
	m_previewImage->SetSize(0.5f, 0.5f);
	m_previewImage->SetPosition(m_position + D3DXVECTOR2(3, 7));
	m_previewImage->Update();
	m_previewImage->Render();
}

void SpringPlatform::SetPreviewImageColor(D3DXCOLOR color)
{
	m_previewImage->SetColor(color);
}

bool SpringPlatform::CanPlaceObject(int h, int w, Map * map)
{
	return !(map->GetCellStatus(h, w));
}

void SpringPlatform::PlaceObject(int h, int w, Map * map)
{
	map->SetCellStatus(h, w, true);
}
