#include "stdafx.h"
#include "Player.h"
#include "Map.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::Init(Map* map)
{
	m_map = map;

	m_AABB = new AABB({ 40.0f, 53.0f });
	m_AABB->Init();

	m_AABBOffset = { 0.0f, 0.0f };

	m_jumpSpeed = 500.0f;
	m_maxWalkSpeed = 400.0f;
	m_walkSpeed = 0.0f;

	m_curState = STATE::Stand;
	m_position = { WINSIZEX*0.5f, WINSIZEY };
	m_oldPosition = m_position;
	m_pressingJumpingButton = false;

	m_fallingSpeedBound = -1500.0f;
}

void Player::Update()
{

	// ����, ������ �̵�
	if (g_pKeyManager->IsStayKeyDown(VK_LEFT) == g_pKeyManager->IsStayKeyDown(VK_RIGHT))
	{
		m_walkSpeed = 0.0f;
	}
	else if (g_pKeyManager->IsStayKeyDown(VK_LEFT))
	{
		if (m_walkSpeed > 0.0f) m_walkSpeed = 0.0f;
		m_walkSpeed -= m_maxWalkSpeed * 3.5f* g_pTimeManager->GetDeltaTime();
		if (fabs(m_walkSpeed) > m_maxWalkSpeed) m_walkSpeed = -m_maxWalkSpeed;
	}
	else if (g_pKeyManager->IsStayKeyDown(VK_RIGHT))
	{
		if (m_walkSpeed < 0.0f) m_walkSpeed = 0.0f;
		m_walkSpeed += m_maxWalkSpeed * 3.5f* g_pTimeManager->GetDeltaTime();
		if (fabs(m_walkSpeed) > m_maxWalkSpeed) m_walkSpeed = m_maxWalkSpeed;
	}

	switch (m_curState)
	{
	case STATE::Stand:
		m_speed = { 0.0f, 0.0f };
		// show the appropriate sprite for the state.
		//...
		if (!m_onGround) m_curState = STATE::Jump;
		if (g_pKeyManager->IsStayKeyDown(VK_LEFT) || g_pKeyManager->IsStayKeyDown(VK_RIGHT))
		{
			m_curState = STATE::Walk;
		}
		if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
		{
			m_speed.y = m_jumpSpeed;
			m_curState = STATE::Jump;
			m_pressingJumpingButton = true;
		}
		break;		
	case STATE::Walk:
		if (!m_onGround)
		{
			m_curState = STATE::Jump;
			break;
		}
		m_speed = { m_walkSpeed, 0.0f };

		// ����
		if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
		{
			m_speed.y = m_jumpSpeed;
			m_curState = STATE::Jump;
			m_pressingJumpingButton = true;
		}
		break; 
	case STATE::Jump:
		if (m_onGround)
		{
			m_speed.y = 0.0f;
			m_curState = STATE::Stand;
			break;
		}
		// �����߿� ����, ������ �̵�
		if (g_pKeyManager->IsStayKeyDown(VK_LEFT) == g_pKeyManager->IsStayKeyDown(VK_RIGHT))
		{
			if(!m_isWallJumpingTowardLeft && !m_isWallJumpingTowardRight)
				m_speed.x = 0.0f;
		}
		else if (g_pKeyManager->IsStayKeyDown(VK_LEFT))
		{
			// ��������
			if(m_isWallJumpingTowardLeft || m_isWallJumpingTowardRight)
			{
				m_speed.x += m_walkSpeed * 2.5f * g_pTimeManager->GetDeltaTime();
				if (m_speed.x < -m_maxWalkSpeed)
				{
					m_isWallJumpingTowardLeft = m_isWallJumpingTowardRight = false;
					m_speed.x = -m_maxWalkSpeed;
				}
			}
			else
			{
				m_speed.x = m_walkSpeed;
			}
		}
		else if (g_pKeyManager->IsStayKeyDown(VK_RIGHT))
		{
			// ��������
			if (m_isWallJumpingTowardLeft || m_isWallJumpingTowardRight)
			{
				m_speed.x += m_walkSpeed * 2.5f * g_pTimeManager->GetDeltaTime();
				if (m_speed.x > m_maxWalkSpeed)
				{
					m_isWallJumpingTowardLeft = m_isWallJumpingTowardRight = false;
					m_speed.x = m_maxWalkSpeed;
				}
			}
			else
			{
				m_speed.x = m_walkSpeed;
			}
		}

		// �߷� ����
		m_speed.y -= GRAVITY * g_pTimeManager->GetDeltaTime();	// �⺻ �߷� ����
		m_pressingJumpingButton = g_pKeyManager->IsStayKeyDown(VK_SPACE) && m_pressingJumpingButton; // ó�� ���� ���� �� ��� ���� ��ư�� ������ �ִ°�?
		if (!m_pressingJumpingButton || m_speed.y < 0)
		{
			m_speed.y -= 3.5f * GRAVITY * g_pTimeManager->GetDeltaTime();	// ������ �� �߰� �߷� ����
		}

		// ������
		if (g_pKeyManager->IsOnceKeyDown(VK_SPACE) && m_isWallSliding)
		{
			// �����̵� ���� ���� �ݴ� �������� ƨ�ܳ�����
			if (m_pushesLeftWall)
			{
				m_speed.x = m_jumpSpeed * 0.7f;
				m_isWallJumpingTowardRight = true;
			}
			else
			{
				m_speed.x = -m_jumpSpeed * 0.7f;
				m_isWallJumpingTowardLeft = true;
			}
			m_speed.y = m_jumpSpeed;
			m_pressingJumpingButton = true;
		}
		break;
	case STATE::GrabLedge:
		break;
	}

	UpdatePhysics();

	if (m_onGround && !m_wasOnGround)
	{
		// ��� ���� ������
		// ���� ����Ʈ �� ���� ������ ȿ�� �ֱ�
	}
}

void Player::UpdatePhysics()
{
	// ĳ������ x ��ġ ������Ʈ (������ �浹 ������ ����)
	m_position.x += m_speed.x * g_pTimeManager->GetDeltaTime();

	// ���� �� �浹
	float leftWallX;
	bool hasLeftWall = m_speed.x < 0 && HasLeftWall(m_oldPosition, m_position, leftWallX) && m_oldPosition.x >= leftWallX;
	if (hasLeftWall)
	{
		m_position.x = leftWallX + m_AABB->GetHalfSize().x;
		m_speed.x = 0.0f;
		m_pushesLeftWall = true;
	}
	else
	{
		m_pushesLeftWall = false;
	}

	// ������ �� �浹
	float rightWallX;
	bool hasRightWall = m_speed.x > 0 && HasRightWall(m_oldPosition, m_position, rightWallX);
	if (hasRightWall)
	{
		m_position.x = rightWallX - m_AABB->GetHalfSize().x;
		m_speed.x = 0.0f;
		m_pushesRightWall = true;
	}
	else
	{
		m_pushesRightWall = false;
	}

	// ĳ������ y ��ġ ������Ʈ (������ �浹 ������ ����)
	m_position.y = max(m_fallingSpeedBound, m_position.y);
	m_position.y += m_speed.y * g_pTimeManager->GetDeltaTime();

	// �Ʒ��� �� �浹
	float groundY;
	bool hasGround = m_speed.y <= 0 && HasGround(m_oldPosition, m_position, m_speed, groundY);
	if (hasGround)
	{
		m_position.y = groundY + m_AABB->GetHalfSize().y;
		m_speed.y = 0.0f;
		m_onGround = true;
	}
	else
	{
		m_onGround = false;
	}

	// ���� �� �浹
	float ceilingY;
	bool hasCeiling = m_speed.y > 0 && HasCeiling(m_oldPosition, m_position, ceilingY);
	if (hasCeiling)
	{
		m_position.y = ceilingY - m_AABB->GetHalfSize().y;
		m_speed.y = 0.0f;
		m_atCeiling = true;
	}
	else
	{
		m_atCeiling = false;
	}

	// �� �����̵�
	m_isWallSliding = (hasLeftWall || hasRightWall) && !hasGround && !hasCeiling && m_speed.y < 0.0f;

	// ������ ���� ���� ������Ʈ
	m_oldPosition = m_position;
	m_oldSpeed = m_speed;

	m_wasOnGround = m_onGround;
	m_pushedRightWall = m_pushesRightWall;
	m_pushedLeftWall = m_pushesLeftWall;
	m_wasAtCeiling = m_atCeiling;
	m_wasWallSliding = m_isWallSliding;

	m_hasNoWalls = !hasLeftWall && !hasRightWall && !hasGround && !hasCeiling;
	m_isWallJumpingTowardLeft = m_isWallJumpingTowardLeft && m_hasNoWalls && !g_pKeyManager->IsStayKeyDown(VK_LEFT);
	m_isWallJumpingTowardRight = m_isWallJumpingTowardRight && m_hasNoWalls && !g_pKeyManager->IsStayKeyDown(VK_RIGHT);

	// AABB ��ġ ������Ʈ
	m_AABB->SetCenter(m_position + m_AABBOffset);
}

bool Player::HasGround(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, D3DXVECTOR2 speed, float & groundY)
{
	// ĳ���� �� ���� �˻�
	D3DXVECTOR2 oldBottomLeft = oldPosition - m_AABB->GetHalfSize(); oldBottomLeft.x += 2; oldBottomLeft.y -= 1;
	D3DXVECTOR2 newBottomLeft = position - m_AABB->GetHalfSize(); newBottomLeft.x += 2; newBottomLeft.y -= 1;
	D3DXVECTOR2 newBottomRight = { newBottomLeft.x + 2 * m_AABB->GetHalfSize().x - 4, newBottomLeft.y };

	// ������Ʈ�� �� ������ ���� ���� �̵��� ���� �� �����Ƿ� ���� ��ġ�� ���� ��ġ ���� ���̵� ����Ͽ� �˻��Ѵ�
	int endTileY = m_map->GetTilePointAtWorldPoint(newBottomLeft).y;
	int beginTileY = max(m_map->GetTilePointAtWorldPoint(oldBottomLeft).y, endTileY); 
	int dist = beginTileY - endTileY;

	// ������ �Ʒ��� �˻�
	for (int TileY = beginTileY; TileY >= endTileY; --TileY)
	{
		float t = (TileY == endTileY) ? 0.0f : ((float)TileY - endTileY) / dist; // ���������� ���� ���� (0~1)
		D3DXVECTOR2 bottomLeft = LinearInterpolation(newBottomLeft, oldBottomLeft, t);
		D3DXVECTOR2 bottomRight = { bottomLeft.x + 2 * m_AABB->GetHalfSize().x - 4, bottomLeft.y };
	
		// bottomLeft���� bottomRight������ �մ� ���� ��� ��� Ÿ�ϵ��� �˻��Ѵ�
		for (D3DXVECTOR2 checkPoint = bottomLeft; ;checkPoint.x = min(checkPoint.x + TILE_SIZE, bottomRight.x))
		{
			POINT tileIdx = m_map->GetTilePointAtWorldPoint(checkPoint);
			if (m_map->IsGround(tileIdx.x, tileIdx.y))
			{
				// ground�� ��� �� Ÿ���� ���κ� y��ǥ�� �����ϰ� true ��ȯ
				groundY = m_map->GetTileTop(tileIdx);
				return true;
			}

			// break ���� : bottomRight�� �ش��ϴ� Ÿ�ϱ��� �˻� �Ϸ�
			if (checkPoint.x >= bottomRight.x) break;
		}
	}

	return false;
}

bool Player::HasCeiling(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float & ceilingY)
{
	// ĳ���� �Ӹ� ���� �˻�
	D3DXVECTOR2 oldtopRight = oldPosition + m_AABB->GetHalfSize(); oldtopRight.x -= 2; oldtopRight.y += 1;
	D3DXVECTOR2 newtopRight = position + m_AABB->GetHalfSize(); newtopRight.x -= 2; newtopRight.y += 1;
	D3DXVECTOR2 newTopLeft = { newtopRight.x + 4 - m_AABB->GetHalfSize().x * 2, newtopRight.y };

	// ������Ʈ�� �� ������ ���� ���� �̵��� ���� �� �����Ƿ� ���� ��ġ�� ���� ��ġ ���� ���̵� ����Ͽ� �˻��Ѵ�
	int endTileY = m_map->GetTilePointAtWorldPoint(newtopRight).y;
	int beginTileY = min(m_map->GetTilePointAtWorldPoint(oldtopRight).y, endTileY);
	int dist = endTileY - beginTileY;

	// �ؿ��� ���� �˻�
	for (int TileY = beginTileY; TileY <= endTileY; ++TileY)
	{
		float t = (TileY == endTileY) ? 0.0f : ((float)endTileY - TileY) / dist; // ���������� ���� ���� (0~1)
		D3DXVECTOR2 topRight = LinearInterpolation(newtopRight, oldtopRight, t);
		D3DXVECTOR2 topLeft = { topRight.x + 4 - m_AABB->GetHalfSize().x * 2, topRight.y };

		// topLeft���� topRight������ �մ� ���� ��� ��� Ÿ�ϵ��� �˻��Ѵ�
		for (D3DXVECTOR2 checkPoint = topLeft; ; checkPoint.x = min(checkPoint.x + TILE_SIZE, topRight.x))
		{
			POINT tileIdx = m_map->GetTilePointAtWorldPoint(checkPoint);
			if (m_map->IsObstacle(tileIdx.x, tileIdx.y))
			{
				// ��ֹ� Ÿ���� �غκ� y��ǥ�� �����ϰ� true ��ȯ
				ceilingY = m_map->GetTileBottom(tileIdx);
				return true;
			}

			// break ���� : topRight�� �ش��ϴ� Ÿ�ϱ��� �˻� �Ϸ�
			if (checkPoint.x >= topRight.x) break;
		}
	}

	return false;
}

bool Player::HasLeftWall(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float & WallX)
{
	// ĳ���� ������ �˻�
	D3DXVECTOR2 oldLeftBottom = oldPosition - m_AABB->GetHalfSize(); oldLeftBottom.x -= 1; oldLeftBottom.y += 2;
	D3DXVECTOR2 newLeftBottom = position - m_AABB->GetHalfSize(); newLeftBottom.x -= 1; newLeftBottom.y += 2;
	D3DXVECTOR2 newLeftTop = { newLeftBottom.x, newLeftBottom.y - 4 + m_AABB->GetHalfSize().y * 2 };

	// ������Ʈ�� �� ������ ���� ���� �̵��� ���� �� �����Ƿ� ���� ��ġ�� ���� ��ġ ���� ���̵� ����Ͽ� �˻��Ѵ�
	int endTileX = m_map->GetTilePointAtWorldPoint(newLeftBottom).x;
	int beginTileX = max(m_map->GetTilePointAtWorldPoint(oldLeftBottom).x, endTileX);
	int dist = beginTileX - endTileX;

	// �����ʿ��� �������� �˻�
	for (int TileX = beginTileX; TileX >= endTileX; --TileX)
	{
		float t = (TileX == endTileX) ? 0.0f : ((float)TileX - endTileX) / dist; // ���������� ���� ���� (0~1)
		D3DXVECTOR2 leftBottom = LinearInterpolation(newLeftBottom, oldLeftBottom, t);
		D3DXVECTOR2 leftTop = { leftBottom.x, leftBottom.y - 4 + m_AABB->GetHalfSize().y * 2 };

		// leftBottom���� leftTop������ �մ� ���� ��� ��� Ÿ�ϵ��� �˻��Ѵ�
		for (D3DXVECTOR2 checkPoint = leftBottom; ; checkPoint.y = min(checkPoint.y + TILE_SIZE, leftTop.y))
		{
			POINT tileIdx = m_map->GetTilePointAtWorldPoint(checkPoint);
			if (m_map->IsObstacle(tileIdx.x, tileIdx.y))
			{
				// ��ֹ� Ÿ���� ������ �𼭸� x��ǥ�� �����ϰ� true ��ȯ
				WallX = m_map->GetTileRight(tileIdx);
				return true;
			}

			// break ���� : leftTop�� �ش��ϴ� Ÿ�ϱ��� �˻� �Ϸ�
			if (checkPoint.y >= leftTop.y) break;
		}
	}

	return false;
}

bool Player::HasRightWall(D3DXVECTOR2 oldPosition, D3DXVECTOR2 position, float & WallX)
{
	// ĳ���� �������� �˻�
	D3DXVECTOR2 oldRightTop = oldPosition + m_AABB->GetHalfSize(); oldRightTop.x += 1; oldRightTop.y -= 2;
	D3DXVECTOR2 newRightTop = position + m_AABB->GetHalfSize(); newRightTop.x += 1; newRightTop.y -= 2;
	D3DXVECTOR2 newRightBottom = { newRightTop.x, newRightTop.y + 4 - m_AABB->GetHalfSize().y * 2 };

	// ������Ʈ�� �� ������ ���� ���� �̵��� ���� �� �����Ƿ� ���� ��ġ�� ���� ��ġ ���� ���̵� ����Ͽ� �˻��Ѵ�
	int endTileX = m_map->GetTilePointAtWorldPoint(newRightTop).x;
	int beginTileX = min(m_map->GetTilePointAtWorldPoint(oldRightTop).x, endTileX);
	int dist = endTileX - beginTileX;

	// ���ʿ��� ���������� �˻�
	for (int TileX = beginTileX; TileX <= endTileX; ++TileX)
	{
		float t = (TileX == endTileX) ? 0.0f : ((float)endTileX - TileX) / dist; // ���������� ���� ���� (0~1)
		D3DXVECTOR2 rightTop = LinearInterpolation(newRightTop, oldRightTop, t);
		D3DXVECTOR2 rightBottom = { rightTop.x, rightTop.y + 4 - m_AABB->GetHalfSize().y * 2 };

		// rigghtBottom���� rightTop������ �մ� ���� ��� ��� Ÿ�ϵ��� �˻��Ѵ�
		for (D3DXVECTOR2 checkPoint = rightBottom; ; checkPoint.y = min(checkPoint.y + TILE_SIZE, rightTop.y))
		{
			POINT tileIdx = m_map->GetTilePointAtWorldPoint(checkPoint);
			if (m_map->IsObstacle(tileIdx.x, tileIdx.y))
			{
				// ��ֹ� Ÿ���� ���� �𼭸� x��ǥ�� �����ϰ� true ��ȯ
				WallX = m_map->GetTileLeft(tileIdx);
				return true;
			}

			// break ���� : rightTop�� �ش��ϴ� Ÿ�ϱ��� �˻� �Ϸ�
			if (checkPoint.y >= rightTop.y) break;
		}
	}

	return false;
}

void Player::Render()
{
	m_AABB->Render();
}

void Player::Release()
{
	m_AABB->Release();
	SAFE_DELETE(m_AABB);
}
