#include "stdafx.h"
#include "BallShooter.h"
#include "Player.h"
#include "Primitive2DObejct.h"
#include "Ball.h"
#include "Map.h"

BallShooter::BallShooter()
{
	m_machineSprite = new Sprite(L"Object-Sheet-1", 6, 6, 1);
	m_machineSprite->SetSize(0.7f, 0.7f);
	m_shootDelay = 3.5f;
	m_AABB = new AABB;
	m_AABB->SetHalfSize({ 25.0f, 25.0f });

	m_machineOffset = { 0,20 };
}

BallShooter::~BallShooter()
{
}

void BallShooter::Init()
{

	for (int i = 0; i < 5; ++i)
	{
		auto ball = new Ball;
		ball->SetFlip(m_flipped);
		ball->Init();
		m_disabledBalls.push_back(ball);
	}

	if (m_flipped)
	{
		m_machineSprite->SetRotation(0, D3DX_PI, 0);
		m_shootStartPoint = D3DXVECTOR2( m_position.x - 20.0f, m_position.y ) + m_machineOffset;
		m_shootStartSpeed = D3DXVECTOR2(-600.f, 500.0f);
	}
	else
	{
		m_shootStartPoint = D3DXVECTOR2( m_position.x + 20.0f, m_position.y ) + m_machineOffset;
		m_shootStartSpeed = D3DXVECTOR2(600.f, 500.0f);
	}
}

void BallShooter::Update(vector<vector<PlaceableObject*>>& objList)
{
	if (m_shootDelayCount >= m_shootDelay)
	{
		m_shootDelayCount = 0.0f;

		// shoot ball
		if (m_disabledBalls.size() <= 0)
		{
			// 새로운 공 추가
			auto ball = new Ball;
			ball->SetFlip(m_flipped);
			ball->Init();
			m_disabledBalls.push_back(ball);
		}

		// disable된 공들 중 하나를 발사시킨다
		Ball* pBall = m_disabledBalls.front(); m_disabledBalls.pop_front();
		pBall->m_position = m_shootStartPoint;
		pBall->SetSpeed(m_shootStartSpeed);
		pBall->SetEnabled(true);
		m_enabledBalls.push_back(pBall);
	}

	m_shootDelayCount += g_pTimeManager->GetDeltaTime();

	// 활성화 된 Ball들 업데이트
	for (auto it = m_enabledBalls.begin(); it != m_enabledBalls.end(); ++it)
	{
		Ball* pBall = *(it);
		// 게임 화면의 범위를 벗어났거나 disable된 발사체에 대해서는 Update를 skip하고 비활성화된 발사체들의 벡터에 저장한다
		if (pBall->m_position.x + m_machineOffset.x < 0 || pBall->m_position.x + m_machineOffset.x > GAMESCREEN_X ||
			pBall->m_position.y + m_machineOffset.y < 0 || pBall->m_position.y + m_machineOffset.y > GAMESCREEN_Y || !pBall->GetEnabled())
		{
			pBall->SetEnabled(false);
			m_disabledBalls.push_back(pBall);
			m_enabledBalls.erase(it);
			break;
		}
		pBall->Update(objList);
	}

	m_AABB->SetCenter(m_position + m_machineOffset);
	m_machineSprite->SetPosition(m_position + m_machineOffset);
	m_machineSprite->Update();

	PlaceableObject::RegisterObjectCollider(m_AABB, objList);
}

void BallShooter::Render()
{
	// 활성화 된 Ball들 렌더
	for (auto pBall : m_enabledBalls)
	{
		pBall->Render();
	}
	m_machineSprite->Render();
	m_AABB->Render();
}

void BallShooter::Release()
{
	SAFE_DELETE(m_AABB);
	SAFE_DELETE(m_machineSprite);
	m_disabledBalls.clear();
	m_enabledBalls.clear();
}

bool BallShooter::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
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

void BallShooter::RenderPreviewImage()
{
	m_machineSprite->SetPosition(m_position + m_machineOffset);
	float rotate = (m_flipped) ? D3DX_PI : 0;
	m_machineSprite->SetRotation({ 0,rotate,0 });
	m_machineSprite->Update();
	m_machineSprite->Render();

	m_machineSprite->SetSize(0.7f, 0.7f);
}

void BallShooter::SetPreviewImageColor(D3DXCOLOR color)
{
	m_machineSprite->SetColor(color);
}

bool BallShooter::CanPlaceObject(int h, int w, Map * map)
{
	return !(map->GetCellStatus(h, w));
}

void BallShooter::PlaceObject(int h, int w, Map * map)
{
	map->SetCellStatus(h, w, true);
}
