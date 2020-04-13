#include "stdafx.h"
#include "GoalFlag.h"


GoalFlag::GoalFlag()
{
	m_pAnimation = new Animation<ANIM_STATE>;
	m_poleSprite = new Sprite(L"Flag-Pole", 1, 1, 0);
	m_poleSprite->SetColor({ 0.2f, 0.2f, 0.2f, 1 });

	Clip* clip = new Clip;
	Sprite* sprite;
	for (int i = 0; i < 15; ++i)
	{
		sprite = new Sprite(L"Flag-Sheet", 3, 5, i);
		sprite->SetColor({ 0.8f, 0.2f, 0, 1 });
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(ANIM_STATE::IDLE, clip);
	m_pAnimation->SetScale(0.4f, 0.4f);
	m_poleSprite->SetSize(0.4f, 0.4f);
	m_poleOffset = { -40, -40 };
}


GoalFlag::~GoalFlag()
{
}

void GoalFlag::Init()
{
	m_pAnimation->Play(ANIM_STATE::IDLE);
}

void GoalFlag::Update(vector<vector<PlaceableObject*>>& objList)
{
	m_poleSprite->SetPosition(m_position + m_poleOffset);
	m_poleSprite->Update();
	m_pAnimation->SetPosition(m_position);
	m_pAnimation->Update();

	//RegisterObjectCollider(Collider * collider, vector<vector<PlaceableObject*>>& objList)
}

void GoalFlag::Render()
{
	m_pAnimation->Render();
	m_poleSprite->Render();
}

void GoalFlag::Release()
{
	SAFE_DELETE(m_poleSprite);
	SAFE_DELETE(m_pAnimation);
}

bool GoalFlag::handleCollision(D3DXVECTOR2 pos, Player * player, collisionCheckDir dir)
{
	return false;
}

void GoalFlag::RenderPreviewImage()
{
	m_poleSprite->Render();
	m_pAnimation->Render();
}
