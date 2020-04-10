#include "stdafx.h"
#include "BallShooter.h"
#include "Player.h"
#include "Primitive2DObejct.h"

BallShooter::BallShooter()
{
	m_ballSprite = new Sprite(L"Object-Sheet-1", 6, 6, 2);
	m_machineSprite = new Sprite(L"Object-Sheet-1", 6, 6, 1);
	m_ballSprite->SetSize(0.9f, 0.9f);
	m_machineSprite->SetSize(0.7f, 0.7f);
}

BallShooter::~BallShooter()
{
}

void BallShooter::Init()
{
	m_shootDelay = 3.5f;
	m_AABB = new AABB;
	m_AABB->SetHalfSize({ 25.0f, 25.0f });
	
	if (m_flipped) m_ballSprite->SetRotation(0, D3DX_PI, 0);

	for (int i = 0; i < 5; ++i)
		m_disabledBalls.emplace_back(new Ball(m_flipped));

	if (m_flipped)
	{
		m_machineSprite->SetRotation(0, D3DX_PI, 0);
		m_shootStartPoint = { m_position.x - 20.0f, m_position.y };
		m_shootStartSpeed = D3DXVECTOR2(-600.f, 500.0f);
	}
	else
	{
		m_shootStartPoint = { m_position.x + 20.0f, m_position.y };
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
			m_disabledBalls.emplace_back(new Ball(m_flipped));
		}
		Ball* pBall = m_disabledBalls.front(); m_disabledBalls.pop_front();
		pBall->m_position = m_shootStartPoint;
		pBall->m_speed = m_shootStartSpeed;
		//pBall->SetDestroyed(false);
		m_enabledBalls.push_back(pBall);
	}

	m_shootDelayCount += g_pTimeManager->GetDeltaTime();

	// Ȱ��ȭ �� Ball�� ������Ʈ
	for (auto it = m_enabledBalls.begin(); it != m_enabledBalls.end(); ++it)
	{
		Ball* pBall = *(it);
		// ���� ȭ���� ������ ����ų� �ı��� �߻�ü�� ���ؼ��� Update���� �ʰ� ��Ȱ��ȭ�� �߻�ü���� ���Ϳ� �����Ѵ�
		if (pBall->m_position.x < 0 || pBall->m_position.x > GAMESCREEN_X ||
			pBall->m_position.y < 0 || pBall->m_position.y > GAMESCREEN_Y )//|| pBall->IsDestroyed())
		{
			m_disabledBalls.push_back(pBall);
			m_enabledBalls.erase(it);
			break;
		}
		pBall->Update();
	}

	m_AABB->SetCenter(m_position);
	m_machineSprite->SetPosition(m_position);
	m_machineSprite->Update();
}

void BallShooter::Render()
{
	// Ȱ��ȭ �� Ball�� ����
	for (auto pBall : m_enabledBalls)
	{
		m_ballSprite->SetPosition({ pBall->m_position.x,  pBall->m_position.y + 4});
		((Primitive2DObejct<Sprite>*)m_ballSprite)->RotateAroundPointAndUpdate(
			{ 0, 0, tanhf(pBall->m_speed.y / pBall->m_speed.x) }, (m_flipped ? D3DXVECTOR2(15, 0) : D3DXVECTOR2(-15, 0)));
		m_ballSprite->Render();
		pBall->Render();
	}
	m_machineSprite->Render();
	m_AABB->Render();
}

void BallShooter::Release()
{
	SAFE_DELETE(m_AABB);
	SAFE_DELETE(m_ballSprite);
	SAFE_DELETE(m_machineSprite);
	m_disabledBalls.clear();
}

bool BallShooter::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	// �÷��̾�� �߻�ü�� �浹�ߴٸ� �÷��̾� ���
	for (auto it = m_enabledBalls.begin(); it != m_enabledBalls.end(); ++it)
	{
		Ball* pBall = *(it);
		if (CircleCollision(pBall->m_circle->GetCenter(), pBall->m_circle->GetHalfSize().x,
			player->m_position, min(player->GetAABBHalfSize().x, player->GetAABBHalfSize().y)) ||
			pBall->m_circle->pointInCollider(pos))
		{
			pBall->Destory();
			player->Die();
			break;
		}
	}
}

void BallShooter::RenderPreviewImage()
{
	m_machineSprite->SetPosition(m_position);
	m_machineSprite->SetSize(1,1);
	float rotate = (m_flipped) ? D3DX_PI : 0;
	m_machineSprite->SetRotation({ 0,rotate,0 });
	m_machineSprite->Update();
	m_machineSprite->Render();

	m_machineSprite->SetSize(0.7f, 0.7f);
}

BallShooter::Ball::Ball(bool flipped): m_isFlipped(flipped)
{
	m_circle = new CircleCollider;
	m_circle->SetHalfSize({ 20.0f, 20.0f });
	m_speed = { 0.0f, 0.0f };
	//Projectile::SetDestroyed(true);
	m_xSpeedBound = (flipped)? -350.0f : 350.0f;
}

void BallShooter::Ball::Update()
{
	m_position += m_speed * g_pTimeManager->GetDeltaTime();
	if (m_isFlipped)
	{
		m_speed.x += 200.0f * g_pTimeManager->GetDeltaTime();
		m_speed.x = min(m_speed.x, m_xSpeedBound);
		m_circle->SetCenter({ m_position.x, m_position.y });
	}
	else
	{
		m_speed.x -= 200.0f * g_pTimeManager->GetDeltaTime();
		m_speed.x = max(m_speed.x, m_xSpeedBound);
		m_circle->SetCenter({ m_position.x, m_position.y });
	}
	
	m_speed.y -= GRAVITY * g_pTimeManager->GetDeltaTime();
}

void BallShooter::Ball::Render()
{
	m_circle->Render();
}

void BallShooter::Ball::Destory()
{
	//Projectile::SetDestroyed(true);
}

bool BallShooter::Ball::Collide(void * other)
{
	return false;
}