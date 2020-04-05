#include "stdafx.h"
#include "SpinWheel.h"
#include "Player.h"

SpinWheel::SpinWheel(D3DXVECTOR2 pos) : m_position(pos)
{
	m_AABB = new AABB({ 25.0f, 25.0f });
	m_AABB->Init();

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

}


SpinWheel::~SpinWheel()
{
}

void SpinWheel::Init()
{
}

void SpinWheel::Update()
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
}

void SpinWheel::Render()
{
	m_blockSprite->Render();
	m_AABB->Render();
	m_barSprite->Render();
	m_wheelSprite->Render();
}

void SpinWheel::Release()
{
}

bool SpinWheel::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
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
