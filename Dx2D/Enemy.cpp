#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"


Enemy::Enemy()
{
	Clip* clip = new Clip;
	for (int i = 0; i < 2; i++)
	{
		Sprite* sprite = new Sprite(L"Player", 2, 1, i);
		sprite->SetColor(D3DXCOLOR(0, 0, 1, 1));
		clip->AddFrame(sprite, 1 / 2.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Flying, clip);
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	Unit::Init();

	m_vPosition.x = rand() % (int)(g_pCamera->GetMapSize().x);
	m_vPosition.y = rand() % (int)(g_pCamera->GetMapSize().y);

	m_vRotation.z = GetAngleAsRadian(m_vPosition, *m_pPlayer->GetPosition());
}

void Enemy::Update()
{
	m_vPosition.x += cosf(m_vRotation.z) * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	m_vPosition.y += sinf(m_vRotation.z) * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();

	// 플레이어 쫒아오게 하기

	Unit::Update();
}

void Enemy::Render()
{
	Unit::Render();
}
