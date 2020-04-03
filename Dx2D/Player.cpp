#include "stdafx.h"
#include "Player.h"
#include "Map.h"
#include "PlaceableObject.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_AABBHalfSize = { 18.0f, 34.0f };
	m_AABB = new AABB(m_AABBHalfSize);
	m_AABB->Init();

	m_AABBOffset = { 0.0f, 0.0f };

	m_jumpSpeed = 500.0f;
	m_maxWalkSpeed = 400.0f;
	m_walkSpeed = 0.0f;

	m_position = { 500.0f ,800.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };
	m_oldPosition = m_position;
	m_pressingJumpingButton = false;

	m_fallingSpeedBound = -1000.0f;
	m_facingRight = true;

	InitAnimation();

	m_prevAnimState = ANIM_STATE::READY;
	m_animState = ANIM_STATE::IDLE;
	m_curState = STATE::Stand;

	m_isRidingMovingPlatform = false;
}

void Player::InitAnimation()
{
	// 애니메이션 추가
	m_pAnimation = new Animation<ANIM_STATE>;
	
	Clip* clip;
	Sprite* sprite;

	int sheetY = 4;
	int sheetX = 14;

	// IDLE
	clip = new Clip;
	for (int i = 0; i < 3; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, i);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::IDLE, clip);

	// FLIP_STAND
	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 2; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, i + 3);
		clip->AddFrame(sprite, 1 / 20.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::FLIP_STAND, clip);

	// WALK
	clip = new Clip;
	for (int i = 0; i < 8; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, i + 5);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::WALK, clip);

	//JUMP_GOING_UP
	clip = new Clip;
	for (int i = 0; i < 3; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX + i);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::JUMP_GOING_UP, clip);

	// UP_TO_TOP
	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 2; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX * 2 + i + 3);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::UP_TO_TOP, clip);

	//JUMP_TOP
	clip = new Clip;
	for (int i = 0; i < 3; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX + i + 3);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::JUMP_TOP, clip);

	//TOP_TO_DOWN
	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 2; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX + i + 6);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::TOP_TO_DOWN, clip);

	//JUMP_GOING_DOWN
	clip = new Clip();
	for (int i = 0; i < 3; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX*2 + i);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::JUMP_GOING_DOWN, clip);

	//LANDING_SOFT
	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 3; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX + i + 8);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::LANDING_SOFT, clip);

	//JUMP_TOP_FLIP
	clip = new Clip(PlayMode::Once);
	sprite = new Sprite(L"Chicken-Sheet", sheetX / 2, sheetY, sheetX / 2 + 6);
	clip->AddFrame(sprite, 1 / 24.0f);
	m_pAnimation->AddClip(ANIM_STATE::JUMP_TOP_FLIP, clip);

	//WALLSLIDE
	clip = new Clip;
	for (int i = 0; i < 3; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX * 2 + i + 5);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::WALLSLIDE, clip);

	//TO_WALLSLIDE_OPPOSITE_START
	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 2; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX * 2 + i + 8);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::TO_WALLSLIDE_OPPOSITE_START, clip);

	//TOP_TO_WALLSLIDE
	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 2; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX * 2 + i + 10);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::TOP_TO_WALLSLIDE, clip);

	//DEATH_SHOCK
	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 3; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX, sheetY, sheetX * 3 + i);
		clip->AddFrame(sprite, 1 / 16.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::DEATH_SHOCK, clip);

	//DEAD
	clip = new Clip(PlayMode::Once);
	for (int i = 0; i < 5; ++i)
	{
		sprite = new Sprite(L"Chicken-Sheet", sheetX / 2, sheetY, (sheetX/2) * 3 + i + 2);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::DEAD, clip);

	m_pAnimation->SetScale(0.25f, 0.25f);
}

void Player::Update(vector<PlaceableObject*> obj)
{
	if (g_pKeyManager->IsOnceKeyDown(VK_RETURN))
	{
		if (!m_isDead)
			this->Die();
		else
			this->Revive();
		return;
	}

	if (!m_isDead)
	{
		UpdateWalkSpeed();

		switch (m_curState)
		{
		case STATE::Stand:
			UpdateStand();
			break;
		case STATE::Walk:
			UpdateWalk();
			break;
		case STATE::Jump:
			UpdateJump();
			break;
		}
	}
	else
	{
		m_speed.y -= GRAVITY * g_pTimeManager->GetDeltaTime();	// 기본 중력 적용
		m_speed.y = max(m_speed.y, m_fallingSpeedBound);
	}

	UpdatePhysics(obj);
	UpdateAnimation();

	if (m_animState == ANIM_STATE::DEAD)
	{
		m_AABB->SetHalfSize({ m_AABBHalfSize.x, m_AABBHalfSize.y*0.3f });
	}

	// 움직임 상태 정보 갱신
	m_oldPosition = m_position;
	m_oldSpeed = m_speed;
	m_wasOnGround = m_onGround;
	m_pushedRightWall = m_pushesRightWall;
	m_pushedLeftWall = m_pushesLeftWall;
	m_wasAtCeiling = m_atCeiling;
	m_wasWallSliding = m_isWallSliding;
	m_slidRightWall = m_slidesRightWall;
	m_slidLeftWall = m_slidesLeftWall;
}

void Player::UpdateJump()
{
	if (m_onGround)
	{
		m_speed.y = 0.0f;
		m_curState = STATE::Stand;
	}
	else
	{
		// 점프중에 왼쪽, 오른쪽 이동
		if (g_pKeyManager->IsStayKeyDown(VK_LEFT) == g_pKeyManager->IsStayKeyDown(VK_RIGHT))
		{
			if (!m_isWallJumpingTowardLeft && !m_isWallJumpingTowardRight)
				m_speed.x = 0.0f;
		}
		else if (g_pKeyManager->IsStayKeyDown(VK_LEFT))
		{
			// 벽점프중
			if (m_isWallJumpingTowardLeft || m_isWallJumpingTowardRight)
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
			// 벽점프중
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

		// 중력 적용
		m_speed.y -= GRAVITY * g_pTimeManager->GetDeltaTime();	// 기본 중력 적용
		m_pressingJumpingButton = g_pKeyManager->IsStayKeyDown(VK_SPACE) && m_pressingJumpingButton; // 처음 점프 시작 후 계속 점프 버튼을 누르고 있는가?
		if (!m_pressingJumpingButton || m_speed.y < 0)
		{
			m_speed.y -= 4.5f * GRAVITY * g_pTimeManager->GetDeltaTime();	// 떨어질 때 추가 중력 적용
		}
		if (m_isWallSliding)
		{
			m_speed.y = max(m_speed.y, -GRAVITY);
		}

		// 벽점프
		if (g_pKeyManager->IsOnceKeyDown(VK_SPACE) && m_isWallSliding)
		{
			// 슬라이딩 중인 벽의 반대 방향으로 튕겨나간다
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
	}
}

void Player::UpdateWalk()
{
	if (!m_onGround)
	{
		m_curState = STATE::Jump;
	}
	else if (m_walkSpeed == 0.0f)
	{
		m_curState = STATE::Stand;
	}
	else
	{
		m_speed = { m_walkSpeed, 0.0f };

		// 점프
		if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
		{
			m_speed.y = m_jumpSpeed;
			m_curState = STATE::Jump;
			m_pressingJumpingButton = true;
		}
	}
}

void Player::UpdateStand()
{
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
}

void Player::UpdateWalkSpeed()
{
	// 왼쪽, 오른쪽 이동
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
}

void Player::UpdatePhysics(vector<PlaceableObject*> objList)
{
	// AABB 위치 업데이트
	m_AABB->SetCenter(m_position + m_AABBOffset);

	// 근처에 있는 오브젝트들에 대해 충돌검사
	CheckFourSides(objList);

	UpdateWallSlideAndJump();

	// AABB 위치 업데이트
	m_AABB->SetCenter(m_position + m_AABBOffset);
}

void Player::UpdateWallSlideAndJump()
{
	// 벽 슬라이드
	bool wallSlideStart = (m_pushesLeftWall || m_pushesRightWall) && !m_onGround && !m_atCeiling && m_speed.y < 0.0f;
	m_isWallSliding = wallSlideStart || (m_isWallSliding && !m_onGround && !m_atCeiling && m_speed.y < 0.0f);
	if (wallSlideStart)
	{
		m_slidesLeftWall = m_pushesLeftWall;
		m_slidesRightWall = m_pushesRightWall;
	}
	m_slidesLeftWall = m_slidesLeftWall && m_isWallSliding;
	m_slidesRightWall = m_slidesRightWall && m_isWallSliding;

	m_hasNoWalls = !m_pushesLeftWall && !m_pushesRightWall && !m_onGround && !m_atCeiling;
	m_isWallJumpingTowardLeft = m_isWallJumpingTowardLeft && m_hasNoWalls && !g_pKeyManager->IsStayKeyDown(VK_LEFT);
	m_isWallJumpingTowardRight = m_isWallJumpingTowardRight && m_hasNoWalls && !g_pKeyManager->IsStayKeyDown(VK_RIGHT);
}

void Player::CheckFourSides(vector<PlaceableObject*> objList)
{
	// 캐릭터의 x 위치 업데이트 (가로축 충돌 판정을 위해)
	if (!(m_animState == ANIM_STATE::DEATH_SHOCK))
	{
		m_position.x += m_speed.x * g_pTimeManager->GetDeltaTime();
		m_pushesLeftWall = m_pushesRightWall = m_onGround = m_atCeiling = false;
	}
	for (auto obj : objList)
	{
		// 왼쪽 벽 충돌
		m_pushesLeftWall |= m_speed.x <= 0.0f && HasLeftWall(obj, m_oldPosition + m_AABBOffset, m_position + m_AABBOffset);

		// 오른쪽 벽 충돌
		m_pushesRightWall |= m_speed.x >= 0.0f && HasRightWall(obj, m_oldPosition + m_AABBOffset, m_position + m_AABBOffset);
	}

	// 캐릭터의 y 위치 업데이트 (세로축 충돌 판정을 위해)
	if (!(m_animState == ANIM_STATE::DEATH_SHOCK))
	{
		m_speed.y = max(m_fallingSpeedBound, m_speed.y);
		m_position.y += m_speed.y * g_pTimeManager->GetDeltaTime();
	}

	for (auto obj : objList)
	{
		// 아래쪽 벽 충돌
		m_onGround |= m_speed.y <= 0 && HasGround(obj, m_oldPosition + m_AABBOffset, m_position + m_AABBOffset);

		// 위쪽 벽 충돌
		m_atCeiling |= m_speed.y > 0 && HasCeiling(obj, m_oldPosition + m_AABBOffset, m_position + m_AABBOffset);
	}

}

bool Player::HasGround(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position)
{
	// 캐릭터 발 밑을 검사
	int newPixelY = position.y - m_AABB->GetHalfSize().y - 5;
	int oldPixelY = max(newPixelY, oldPosition.y - m_AABB->GetHalfSize().y - 5);
	int startPixelX = position.x - m_AABB->GetHalfSize().x + 2;
	int endPixelX = position.x + m_AABB->GetHalfSize().x - 2;

	// 위에서 아래로 검사
	for (int pixelY = oldPixelY; pixelY >= newPixelY; --pixelY)
	{
		// startPixelX부터 endPixelX지점을 잇는 선에 닿는 모든 AABB들을 검사한다
		for (D3DXVECTOR2 checkPoint = D3DXVECTOR2(startPixelX, pixelY); ; checkPoint.x = min(checkPoint.x + 1, endPixelX))
		{
			if (other->handleCollision(checkPoint, this, PlaceableObject::collisionCheckDir::BOTTOM))
			{
				return true;
			}
			// break 조건 : endPixelX에 해당하는 타일까지 검사 완료
			if (checkPoint.x >= endPixelX) break;
		}
	}

	return false;
}

bool Player::HasCeiling(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position)
{
	// 캐릭터 머리 위를 검사
	int newPixelY = position.y + m_AABB->GetHalfSize().y + 5;
	int oldPixelY = min(newPixelY, oldPosition.y + m_AABB->GetHalfSize().y + 5);
	int startPixelX = position.x - m_AABB->GetHalfSize().x + 2;
	int endPixelX = position.x + m_AABB->GetHalfSize().x - 2;

	// 밑에서 위로 검사
	for (int pixelY = oldPixelY; pixelY <= newPixelY; ++pixelY)
	{
		// startPixelX부터 endPixelX지점을 잇는 선에 닿는 모든 AABB들을 검사한다
		for (D3DXVECTOR2 checkPoint = D3DXVECTOR2(startPixelX, pixelY); ; checkPoint.x = min(checkPoint.x + 1, endPixelX))
		{
			if (other->handleCollision(checkPoint, this, PlaceableObject::collisionCheckDir::CEILING))
			{
				return true;
			}
			// break 조건 : endPixelX에 해당하는 AABB까지 검사 완료
			if (checkPoint.x >= endPixelX) break;
		}
	}

	return false;
}

bool Player::HasLeftWall(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position)
{
	// 캐릭터 왼쪽을 검사
	int newPixelX = position.x - m_AABB->GetHalfSize().x - 2;
	int oldPixelX = max(newPixelX, oldPosition.x - m_AABB->GetHalfSize().x - 2);
	int startPixelY = position.y - m_AABB->GetHalfSize().y + 5;
	int endPixelY = position.y + m_AABB->GetHalfSize().y - 5;

	// 오른쪽에서 왼쪽으로 검사
	for (int pixelX = oldPixelX; pixelX >= newPixelX; --pixelX)
	{
		// startPixelY부터 endPixelY지점을 잇는 선에 닿는 모든 AABB들을 검사한다
		for (D3DXVECTOR2 checkPoint = D3DXVECTOR2(pixelX, startPixelY); ; checkPoint.y = min(checkPoint.y + 1, endPixelY))
		{
			if (other->handleCollision(checkPoint, this, PlaceableObject::collisionCheckDir::LEFT_WALL))
			{
				return true;
			}
			// break 조건 : endPixelY에 해당하는 타일까지 검사 완료
			if (checkPoint.y >= endPixelY) break;
		}
	}

	return false;
}

bool Player::HasRightWall(PlaceableObject* other, D3DXVECTOR2 oldPosition, D3DXVECTOR2 position)
{
	// 캐릭터 오른쪽을 검사
	int newPixelX = position.x + m_AABB->GetHalfSize().x + 2;
	int oldPixelX = min(newPixelX, oldPosition.x + m_AABB->GetHalfSize().x + 2);
	int startPixelY = position.y - m_AABB->GetHalfSize().y + 5;
	int endPixelY = position.y + m_AABB->GetHalfSize().y - 5;

	// 왼쪽에서 오른쪽으로 검사
	for (int pixelX = oldPixelX; pixelX <= newPixelX; ++pixelX)
	{
		// startPixelY부터 endPixelY지점을 잇는 선에 닿는 모든 AABB들을 검사한다
		for (D3DXVECTOR2 checkPoint = D3DXVECTOR2(pixelX, startPixelY); ; checkPoint.y = min(checkPoint.y + 1, endPixelY))
		{
			if (other->handleCollision(checkPoint, this, PlaceableObject::collisionCheckDir::RIGHT_WALL))
			{
				return true;
			}
			// break 조건 : endPixelY에 해당하는 타일까지 검사 완료
			if (checkPoint.y >= endPixelY) break;
		}
	}

	return false;
}

bool Player::IsFlipping()
{
	bool res;

	return (m_facingRight && g_pKeyManager->IsStayKeyDown(VK_LEFT)) || (!m_facingRight && g_pKeyManager->IsStayKeyDown(VK_RIGHT));
}

void Player::GetNextAnimationState()
{
	if (m_isDead)
	{
		m_rotation.y = (m_facingRight) ? 0.0f : D3DX_PI;
		if (m_animState == ANIM_STATE::DEATH_SHOCK)
		{
			if (m_pAnimation->IsDonePlaying(ANIM_STATE::DEATH_SHOCK))
			{
				m_animState = ANIM_STATE::DEAD;
			}
		}
		else if (!(m_animState == ANIM_STATE::DEAD))
		{
			m_animState = ANIM_STATE::DEATH_SHOCK;
		}
		return;
	}

	switch (m_animState)
	{
	case ANIM_STATE::IDLE:
		if (m_curState == STATE::Walk)
		{
			m_animState = ANIM_STATE::WALK;
		}
		if (IsFlipping())
		{
			m_animState = ANIM_STATE::FLIP_STAND;
		}
		if (m_speed.y > 0.0f)
		{
			m_animState = ANIM_STATE::JUMP_GOING_UP;
		}
		if (m_speed.y < 0.0f)
		{
			m_animState = ANIM_STATE::JUMP_TOP;
		}
		break;
	case ANIM_STATE::WALK:
		if (m_curState == STATE::Stand)
		{
			m_animState = ANIM_STATE::IDLE;
		}
		if (m_speed.y > 0.0f)
		{
			m_animState = ANIM_STATE::JUMP_GOING_UP;
		}
		if (m_speed.y < 0.0f)
		{
			m_animState = ANIM_STATE::JUMP_TOP;
		}
		if (IsFlipping())
		{
			m_animState = ANIM_STATE::FLIP_STAND;
		}
		break;
	case ANIM_STATE::FLIP_STAND:
		if (m_pAnimation->IsDonePlaying(ANIM_STATE::FLIP_STAND))
		{
			m_facingRight = !m_facingRight;
			m_rotation.y = (m_facingRight) ? 0.0f : D3DX_PI;
			m_animState = (m_speed.x == 0.0f) ? ANIM_STATE::IDLE : ANIM_STATE::WALK;
		}
		break;
	case ANIM_STATE::JUMP_GOING_UP:
		if (IsFlipping())
		{
			m_animState = ANIM_STATE::JUMP_TOP_FLIP;
		}
		if (0.0f < m_speed.y && m_speed.y <= 100.0f)
		{
			m_animState = ANIM_STATE::UP_TO_TOP;
		}
		if (m_onGround)
		{
			m_animState = ANIM_STATE::LANDING_SOFT;
		}
		if (m_isWallSliding)
		{
			m_animState = ANIM_STATE::TOP_TO_WALLSLIDE;
		}
		break;
	case ANIM_STATE::UP_TO_TOP:
		if (IsFlipping())
		{
			m_animState = ANIM_STATE::JUMP_TOP_FLIP;
		}
		if (m_pAnimation->IsDonePlaying(ANIM_STATE::UP_TO_TOP))
		{
			m_animState = ANIM_STATE::JUMP_TOP;
		}
		if (m_onGround)
		{
			m_animState = ANIM_STATE::LANDING_SOFT;
		}
		if (m_isWallSliding)
		{
			m_animState = ANIM_STATE::TOP_TO_WALLSLIDE;
		}
		break;
	case ANIM_STATE::JUMP_TOP:
		if (IsFlipping())
		{
			m_animState = ANIM_STATE::JUMP_TOP_FLIP;
		}
		if (m_speed.y < 0.0f && m_speed.y <= -250.0f)
		{
			m_animState = ANIM_STATE::TOP_TO_DOWN;
		}
		if (m_onGround)
		{
			m_animState = ANIM_STATE::LANDING_SOFT;
		}
		if (m_isWallSliding)
		{
			m_animState = ANIM_STATE::TOP_TO_WALLSLIDE;
		}
		break;
	case ANIM_STATE::TOP_TO_DOWN:
		if (IsFlipping())
		{
			m_animState = ANIM_STATE::JUMP_TOP_FLIP;
		}
		if (m_pAnimation->IsDonePlaying(ANIM_STATE::TOP_TO_DOWN))
		{
			m_animState = ANIM_STATE::JUMP_GOING_DOWN;
		}
		if (m_onGround)
		{
			m_animState = ANIM_STATE::LANDING_SOFT;
		}
		break;
	case ANIM_STATE::JUMP_GOING_DOWN:
		if (IsFlipping())
		{
			m_animState = ANIM_STATE::JUMP_TOP_FLIP;
		}
		if (m_onGround)
		{
			m_animState = ANIM_STATE::LANDING_SOFT;
		}
		if (m_isWallSliding)
		{
			m_animState = ANIM_STATE::TOP_TO_WALLSLIDE;
		}
		break;
	case ANIM_STATE::LANDING_SOFT:
		if (m_speed.y != 0.0f || m_speed.x != 0.0f)
		{
			m_animState = ANIM_STATE::IDLE;
			GetNextAnimationState();
		}
		if (m_pAnimation->IsDonePlaying(ANIM_STATE::LANDING_SOFT))
		{
			if (m_curState == STATE::Walk)
				m_animState = ANIM_STATE::WALK;
			if (m_curState == STATE::Stand)
				m_animState = ANIM_STATE::IDLE;
		}
		break;
	case ANIM_STATE::JUMP_TOP_FLIP:
		if (m_pAnimation->IsDonePlaying(ANIM_STATE::JUMP_TOP_FLIP))
		{
			m_facingRight = !m_facingRight;
			m_rotation.y = (m_facingRight) ? 0.0f : D3DX_PI;
			if (m_speed.y > 0.0f)
			{
				m_animState = ANIM_STATE::JUMP_GOING_UP;
			}
			else
			{
				m_animState = ANIM_STATE::JUMP_TOP;
			}
			if (m_onGround)
			{
				m_animState = ANIM_STATE::LANDING_SOFT;
			}
		}
		if (m_isWallSliding)
		{
			m_animState = ANIM_STATE::TOP_TO_WALLSLIDE;
		}
		break;
	case ANIM_STATE::TOP_TO_WALLSLIDE:
		// 슬라이딩 하고 있는 벽의 위치에 따라 좌우반전
		if (m_isWallSliding)
		{
			m_facingRight = m_slidesRightWall;
		}
		if (m_pAnimation->IsDonePlaying(ANIM_STATE::TOP_TO_WALLSLIDE))
		{
			m_animState = ANIM_STATE::WALLSLIDE;
		}
		if (!m_isWallSliding)
		{
			m_animState = ANIM_STATE::TO_WALLSLIDE_OPPOSITE_START;
		}
		break;
	case ANIM_STATE::WALLSLIDE:
		// 슬라이딩 하고 있는 벽의 위치에 따라 좌우반전
		if (m_isWallSliding)
		{
			m_facingRight = m_slidesRightWall;
		}
		if (!m_isWallSliding)
		{
			m_animState = ANIM_STATE::TO_WALLSLIDE_OPPOSITE_START;
			GetNextAnimationState();
		}
		break;
	case ANIM_STATE::TO_WALLSLIDE_OPPOSITE_START:
		if (m_onGround)
		{
			if (m_curState == STATE::Walk || m_pAnimation->IsDonePlaying(ANIM_STATE::TO_WALLSLIDE_OPPOSITE_START))
			{
				// 착지로 벽 슬라이드가 끝났을 때 방향 반전
				m_facingRight = m_slidLeftWall;
				m_animState = ANIM_STATE::IDLE;
				GetNextAnimationState();
			}
		}
		else if(!m_isWallSliding)
		{
			// 점프로 벽 슬라이드가 끝났을 때 방향 반전
			m_facingRight =m_slidLeftWall;
			m_animState = ANIM_STATE::JUMP_GOING_UP;
			GetNextAnimationState();
		}
		break;
	}

	m_rotation.y = (m_facingRight) ? 0.0f : D3DX_PI;
}

void Player::UpdateAnimation()
{
	GetNextAnimationState();

	m_pAnimation->SetPosition({ m_position.x,  m_position.y + 7});
	m_pAnimation->SetRotation(m_rotation.x, m_rotation.y, m_rotation.z);
	m_pAnimation->Play(m_animState);
	m_pAnimation->Update();

	// 애니메이션 상태 업데이트
	m_prevAnimState = m_animState;
}

void Player::Render()
{
	m_AABB->Render();
	m_pAnimation->Render();
}

void Player::Release()
{
	m_AABB->Release();
	SAFE_DELETE(m_AABB);
	SAFE_DELETE(m_pAnimation);
}

void Player::Die()
{
	m_isDead = true; 
	m_speed.x = 0.0f; 
}

void Player::Revive()
{
	m_isDead = false;

	m_position = { 500.0f, 800.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };
	m_oldPosition = m_position;
	m_pressingJumpingButton = false;

	m_facingRight = true;

	m_prevAnimState = ANIM_STATE::READY;
	m_animState = ANIM_STATE::IDLE;
	m_curState = STATE::Stand;

	m_isRidingMovingPlatform = false;

	m_AABB->SetHalfSize(m_AABBHalfSize);
}