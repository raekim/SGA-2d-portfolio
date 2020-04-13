#include "stdafx.h"
#include "Ball.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "Player.h"

Ball::Ball()
{
	m_collider = new CircleCollider;
	m_collider->SetHalfSize({ 20.0f, 20.0f });
	m_ballSprite = new Sprite(L"Object-Sheet-1", 6, 6, 2);
	m_ballSprite->SetSize(0.9f, 0.9f);	
}


Ball::~Ball()
{
}

void Ball::Init()
{
	m_speed = { 0.0f, 0.0f };
	if (m_flipped) m_ballSprite->SetRotation(0, D3DX_PI, 0);
	m_xSpeedBound = (m_flipped) ? -350.0f : 350.0f;
}

void Ball::Update(vector<vector<PlaceableObject*>>& objList)
{
	// 공이 날아간다
	m_position += m_speed * g_pTimeManager->GetDeltaTime();

	// 좌/우 반전에 따라 공이 날아가는 방향이 다르다
	if (m_flipped)
	{
		m_speed.x += 200.0f * g_pTimeManager->GetDeltaTime();
		m_speed.x = min(m_speed.x, m_xSpeedBound);
		m_collider->SetCenter(m_position);
	}
	else
	{
		m_speed.x -= 200.0f * g_pTimeManager->GetDeltaTime();
		m_speed.x = max(m_speed.x, m_xSpeedBound);
		m_collider->SetCenter(m_position);
	}

	// 이미지 업데이트
	m_ballSprite->SetPosition({ m_position.x,  m_position.y + 4 });
	((Primitive2DObejct<Sprite>*)m_ballSprite)->RotateAroundPointAndUpdate(
		{ 0, 0, tanhf(m_speed.y / m_speed.x) }, (m_flipped ? D3DXVECTOR2(15, 0) : D3DXVECTOR2(-15, 0)));

	// 중력 적용
	m_speed.y -= GRAVITY * g_pTimeManager->GetDeltaTime();
	PlaceableObject::RegisterObjectCollider(m_collider, objList);
}

void Ball::Render()
{
	m_ballSprite->Render();
	m_collider->Render();
}

void Ball::Release()
{
	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_ballSprite);
}

bool Ball::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	if (m_enabled)
	{
		// 플레이어와 충돌했다면 플레이어 사망
		if (CircleCollision(m_collider->GetCenter(), m_collider->GetHalfSize().x,
			player->m_position, min(player->GetAABBHalfSize().x, player->GetAABBHalfSize().y)) ||
			m_collider->pointInCollider(pos))
		{
			m_enabled = false;
			player->Die();
			return true;
		}
	}
	return false;
}