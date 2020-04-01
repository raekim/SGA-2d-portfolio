#include "stdafx.h"
#include "honeyPlatform.h"
#include "Player.h"

honeyPlatform::honeyPlatform()
{
}


honeyPlatform::~honeyPlatform()
{
}

void honeyPlatform::Init()
{
	m_AABB = new AABB({ 40.0f, 40.0f });
	m_AABB->Init();

	m_oldPosition = m_position = { WINSIZEX*0.5f - 300.0f, WINSIZEY - 600.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };

	m_movingStartPoint = m_position - D3DXVECTOR2(200.0f, 200.0f);
	m_movingEndPoint = m_position + D3DXVECTOR2(200.0f, 200.0f);

	m_moveSecond = 2.5f;
	m_movingDelta = 0.0f;
}

void honeyPlatform::Update()
{
	m_movingDelta += g_pTimeManager->GetDeltaTime();

	// �� �� �������� �����Ͽ����� �ݴ��� �������� �̵� ������ �ٲ۴�
	if (m_movingDelta >= m_moveSecond)
	{
		m_movingDelta = 0.0f;
		swap(m_movingStartPoint, m_movingEndPoint);
	}

	// �� ������ m_movingStartPoint, m_movingEndPoint ���̸� ���� ������ ����Ͽ� �����δ�
	m_position = LinearInterpolation(m_movingStartPoint, m_movingEndPoint, m_movingDelta / m_moveSecond);
	m_AABB->SetCenter(m_position);
	m_moveDelta = m_position - m_oldPosition;

	m_oldPosition = m_position;
}

void honeyPlatform::Render()
{
	m_AABB->Render();
}

void honeyPlatform::Release()
{
	m_AABB->Release();
}

bool honeyPlatform::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	if (m_AABB->pointInAABB(pos))
	{
		switch (dir)
		{
		case collisionCheckDir::BOTTOM:
			break;
		case collisionCheckDir::CEILING:
			break;
		case collisionCheckDir::LEFT_WALL:
			break;
		case collisionCheckDir::RIGHT_WALL:
			break;
		}
		player->m_movingPlatformOffset = m_moveDelta;
		return true;
	}
	return false;
}
