#include "stdafx.h"
#include "SpinWheel.h"
#include "Player.h"
#include "CircleCollider.h"

SpinWheel::SpinWheel()
{
	m_AABB = new AABB;
	m_AABB->SetHalfSize({ 25.0f, 25.0f });

	m_blockSprite = new Sprite(L"Object-Sheet-1", 6, 6, 14);
	m_blockSprite->SetSize(0.65f, 0.65f);
	m_barSprite = new Sprite(L"Object-Sheet-1", 6, 6, 8);
	m_barSprite->SetSize(0.65f, 0.65f);
	m_wheelSprite = new Sprite(L"Object-Sheet-1", 6, 6, 13);
	m_wheelSprite->SetSize(0.65f, 0.65f);

	m_barRoatationSecond = 3;
	m_wheelRoatationSecond = 2.5f;
	m_barRotationDelta = 0;
	m_wheelRotationDelta = 0;

	m_circle = new CircleCollider;
	m_circle->SetHalfSize({ 20.0f, 20.0f });
}


SpinWheel::~SpinWheel()
{
}

void SpinWheel::Init()
{
}

void SpinWheel::Update(vector<Collider*>& colliders)
{
	m_AABB->SetCenter(m_position);

	m_blockSprite->SetPosition(m_position);
	m_blockSprite->Update();

	m_barRotationAmount = LinearInterpolation(0.0f, static_cast<float>(D3DX_PI * 2), m_barRotationDelta / m_barRoatationSecond);
	m_barSprite->SetPosition(m_position);
	((Primitive2DObejct<Sprite>*)m_barSprite)->RotateAroundPointAndUpdate({ 0, 0, m_barRotationAmount }, D3DXVECTOR2(-5, 44));

	m_wheelRotationAmount = LinearInterpolation(0.0f, static_cast<float>(D3DX_PI * 2), m_wheelRotationDelta / m_wheelRoatationSecond);
	m_wheelSprite->SetRotation({ 0, 0, m_wheelRotationAmount });
	m_wheelSprite->SetPosition(m_position);
	((Primitive2DObejct<Sprite>*)m_wheelSprite)->RotateAroundPointAndUpdate({ 0, 0, m_barRotationAmount }, D3DXVECTOR2(0, 100));

	m_barRotationDelta += g_pTimeManager->GetDeltaTime();
	if (m_barRotationDelta > m_barRoatationSecond) m_barRotationDelta = 0.0f;
	m_wheelRotationDelta += g_pTimeManager->GetDeltaTime();
	if (m_wheelRotationDelta > m_wheelRoatationSecond) m_wheelRotationDelta = 0.0f;

	m_circle->SetCenter(m_position);
	((Primitive2DObejct<Circle>*)m_circle->GetCircle())->RotateAroundPointAndUpdate({ 0, 0, m_barRotationAmount }, D3DXVECTOR2(0, 100));
}

void SpinWheel::Render()
{
	m_blockSprite->Render();
	m_AABB->Render();
	m_barSprite->Render();
	m_wheelSprite->Render();
	m_circle->Render();
}

void SpinWheel::Release()
{
	SAFE_DELETE(m_circle);
	SAFE_DELETE(m_AABB);
	SAFE_DELETE(m_barSprite);
	SAFE_DELETE(m_wheelSprite);
	SAFE_DELETE(m_blockSprite);
}

bool SpinWheel::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	// 플레이어와 톱날이 충돌했다면 플레이어 사망
	// The x, y, and z components of the translation are stored in the ._41, ._42, and ._43 members of the matrix.
	D3DXVECTOR2 circlePos = { m_circle->GetCircle()->GetWMatrix()._41, m_circle->GetCircle()->GetWMatrix()._42 };
	if (CircleCollision(circlePos, m_circle->GetHalfSize().x, player->m_position, min(player->GetAABBHalfSize().x, player->GetAABBHalfSize().y)) ||
		m_circle->pointInCollider(pos))
	{
		player->Die();
	}

	// 블록 부분과 충돌
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

void SpinWheel::RenderPreviewImage()
{
	m_blockSprite->SetPosition(m_position);
	m_barSprite->SetPosition(m_position + D3DXVECTOR2(-5, 40));
	m_wheelSprite->SetPosition(m_position + D3DXVECTOR2(0,90));

	m_blockSprite->Update();
	m_barSprite->Update();
	m_wheelSprite->Update();

	m_blockSprite->SetSize(1,1);
	m_blockSprite->Render();
	m_barSprite->SetSize(0.8f, 0.8f);
	m_barSprite->Render();
	m_wheelSprite->SetSize(1,1);
	m_wheelSprite->Render();

	// 원래 사이즈로 돌아가기
	m_blockSprite->SetSize(0.65f, 0.65f);
	m_barSprite->SetSize(0.65f, 0.65f);
	m_wheelSprite->SetSize(0.65f, 0.65f);
}
