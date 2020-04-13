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
	m_collider = new AABB;
	m_collider->SetHalfSize({ 20.0f, 20.0f });

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

void honeyPlatform::Update(vector<vector<PlaceableObject*>>& objList)
{
	// �� ������ m_movingStartPoint, m_movingEndPoint ���̸� ���� ������ ����Ͽ� �����δ�
	m_cratePosition = LinearInterpolation(m_movingStartPoint, m_movingEndPoint, min(m_movingDelta / m_moveSecond, 1.0f));
	m_collider->SetCenter(m_cratePosition);
	m_moveDelta = m_cratePosition - m_oldPosition;

	// �� �� �������� �����Ͽ����� �ݴ��� �������� �̵� ������ �ٲ۴�
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

	PlaceableObject::RegisterObjectCollider(m_collider, objList);
}

void honeyPlatform::Render()
{
	m_collider->Render();

	m_barSprite->Render();
	m_crateSprite->Render();
}

void honeyPlatform::Release()
{
	SAFE_DELETE(m_crateSprite);
	SAFE_DELETE(m_barSprite);
}

bool honeyPlatform::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	if (m_collider->pointInCollider(pos))
	{
		switch (dir)
		{
		case collisionCheckDir::BOTTOM:

			if (player->m_speed.y < 0.0f)
			{
				player->m_speed.y = 0.0f;
				auto ypos = ((AABB*)m_collider)->GetAABBTop() + player->GetAABBHalfSize().y;
				player->SetPositionY(ypos);
			}
			player->m_position += m_moveDelta;
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
				player->m_speed.x = 0.0f;
				player->SetPositionX(((AABB*)m_collider)->GetAABBRight() + player->GetAABBHalfSize().x);
			}
			player->m_position += m_moveDelta;
			break;
		case collisionCheckDir::RIGHT_WALL:
			if (player->m_speed.x > 0.0f)
			{
				player->m_speed.x = 0.0f;
				player->SetPositionX(((AABB*)m_collider)->GetAABBLeft() - player->GetAABBHalfSize().x);
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
	// ���̾� ����
	float rotate = (m_flipped) ? D3DX_PI : 0;
	m_barSprite->SetPosition(m_position);
	m_barSprite->SetRotation({ 0, rotate, 0 });
	m_barSprite->Update();
	m_barSprite->Render();

	// ��� ����
	m_crateSprite->SetSize({ 0.8f, 0.8f });
	m_crateSprite->SetPosition(m_position);
	m_crateSprite->Update();
	m_crateSprite->Render();
	m_crateSprite->SetSize({ 0.65f, 0.65f });
}
