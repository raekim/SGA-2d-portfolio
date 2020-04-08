#include "stdafx.h"
#include "honeyPlatform.h"
#include "Player.h"

honeyPlatform::honeyPlatform()
{
	m_crateSprite = new Sprite(L"Object-Sheet-1", 6, 6, 7);
	m_barSprite = new Sprite(L"Object-Sheet-1", 2, 2, 1);

	m_crateSprite->SetSize({ 0.65f, 0.65f });
	m_barSprite->SetSize({ 0.6f, 0.6f });
}


honeyPlatform::~honeyPlatform()
{
}

void honeyPlatform::Init()
{
	m_AABB = new AABB({ 20.0f, 20.0f });
	m_AABB->Init();

	m_midPosition = m_position;

	m_moveSecond = 2.5f;
	m_movingDelta = 0.0f;

	if (m_flipped)
	{
		m_movingStartPoint = m_position + D3DXVECTOR2(-130.0f, 130.0f);
		m_movingEndPoint = m_position + D3DXVECTOR2(130.0f, -130.0f);
		m_barSprite->SetRotation(0, D3DX_PI, 0);
		m_barSprite->SetPosition(m_midPosition + D3DXVECTOR2(-7.0f, 0.0f));
		m_barSprite->Update();
	}
	else
	{
		m_movingStartPoint = m_position - D3DXVECTOR2(130.0f, 130.0f);
		m_movingEndPoint = m_position + D3DXVECTOR2(130.0f, 130.0f);
		m_barSprite->SetRotation(0, 0, 0);
		m_barSprite->SetPosition(m_midPosition + D3DXVECTOR2(7.0f, 0.0f));
		m_barSprite->Update();
	}
}

void honeyPlatform::Update()
{
	// 두 기준점 m_movingStartPoint, m_movingEndPoint 사이를 선형 보간을 사용하여 움직인다
	m_cratePosition = LinearInterpolation(m_movingStartPoint, m_movingEndPoint, min(m_movingDelta / m_moveSecond, 1.0f));
	m_AABB->SetCenter(m_cratePosition);
	m_moveDelta = m_cratePosition - m_oldPosition;

	// 한 쪽 기준점에 도달하였으면 반대쪽 정점으로 이동 방향을 바꾼다
	if (m_movingDelta >= m_moveSecond + 0.1f)
	{
		m_movingDelta = 0.0f;
		m_oldPosition = m_cratePosition = m_movingEndPoint;
		swap(m_movingStartPoint, m_movingEndPoint);
	}
	
	m_oldPosition = m_cratePosition;
	m_movingDelta += g_pTimeManager->GetDeltaTime();

	m_crateSprite->SetPosition(m_cratePosition);
	m_crateSprite->Update();
}

void honeyPlatform::Render()
{
	m_AABB->Render();

	m_barSprite->Render();
	m_crateSprite->Render();
}

void honeyPlatform::Release()
{
	m_AABB->Release();
	SAFE_DELETE(m_crateSprite);
	SAFE_DELETE(m_barSprite);
}

bool honeyPlatform::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	if (m_AABB->pointInAABB(pos))
	{
		switch (dir)
		{
		case collisionCheckDir::BOTTOM:
			if (player->m_speed.y < 0.0f)
			{
				player->m_speed.y = 0.0f;
				player->SetPositionY(m_AABB->GetAABBTop() + player->GetAABBHalfSize().y);
			}
			player->m_position += m_moveDelta;
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
			player->m_position += m_moveDelta;
			break;
		case collisionCheckDir::RIGHT_WALL:
			if (player->m_speed.x > 0.0f)
			{
				player->m_speed.x = 0.0f;
				player->SetPositionX(m_AABB->GetAABBLeft() - player->GetAABBHalfSize().x);
			}
			player->m_position += m_moveDelta;
			break;
		}
		return true;
	}
	return false;
}

void honeyPlatform::RenderPreviewImage()
{
	// 와이어 렌더
	float rotate = (m_flipped) ? D3DX_PI : 0;
	m_barSprite->SetPosition(m_position);
	m_barSprite->SetRotation({ 0, rotate, 0 });
	m_barSprite->Update();
	m_barSprite->Render();

	// 블록 렌더
	m_crateSprite->SetSize({ 0.8f, 0.8f });
	m_crateSprite->SetPosition(m_position);
	m_crateSprite->Update();
	m_crateSprite->Render();
	m_crateSprite->SetSize({ 0.65f, 0.65f });
}
