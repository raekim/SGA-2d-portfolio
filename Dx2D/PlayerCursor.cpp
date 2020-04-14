#include "stdafx.h"
#include "PlayerCursor.h"
#include "PlaceableObject.h"
#include "SimplePlatform.h"
#include "Map.h"

PlayerCursor::PlayerCursor()
{
}


PlayerCursor::~PlayerCursor()
{
}

void PlayerCursor::ResetCursor(D3DXVECTOR2 pos)
{
	m_placed = false;
	m_isFlipped = false;
	m_cursorPos = pos;
	SetCursorPosition(m_cursorPos);

	// 커서 위치 설정
	m_cursorDefaultImage->SetPosition(m_cursorPos);
	m_cursorDefaultImage->Update();
	
	// 오브젝트 프리뷰 이미지 위치 설정
	m_objectToPlace->SetPosition(m_map->IndexToPos(m_map->PosToIndex(m_objectPos)));
	m_objectToPlace->SetFlip(m_isFlipped);
}

void PlayerCursor::Init(Sprite * cursorDefaultImg, Sprite * cursorOutOfBoundsImg)
{
	m_cursorDefaultImage = cursorDefaultImg;
	m_cursorOutOfBoundsImage = cursorOutOfBoundsImg;

	m_cursorMoveMaxSpeed = 500.0f;
	m_cursorMoveSpeed = 0.0f;

	m_isFlipped = false;
}

bool PlayerCursor::Update(vector<PlaceableObject*>& objList)
{
	if (m_placed) return m_placed;

	MoveCursor();

	// 오브젝트 flip 하기
	if (g_pKeyManager->IsOnceKeyDown(m_flipKey))
	{
		m_isFlipped = !m_isFlipped;
		m_objectToPlace->SetFlip(m_isFlipped);
	}

	// 오브젝트 놓기
	if (g_pKeyManager->IsOnceKeyDown(m_selectKey))
	{
		m_objectToPlace->SetFlip(m_isFlipped);
		m_objectToPlace->Init();
		objList.push_back(m_objectToPlace);
		m_placed = true;
	}
	return m_placed;
}

void PlayerCursor::MoveCursor()
{
	// 커서 이동
	D3DXVECTOR2 moveVec = { 0,0 };
	bool move = false;
	if (g_pKeyManager->IsStayKeyDown(m_leftMoveKey))
	{
		moveVec.x -= 1;
		move = true;
	}
	if (g_pKeyManager->IsStayKeyDown(m_rightMoveKey))
	{
		moveVec.x += 1;
		move = true;
	}
	if (g_pKeyManager->IsStayKeyDown(m_upMoveKey))
	{
		moveVec.y += 1;
		move = true;
	}
	if (g_pKeyManager->IsStayKeyDown(m_downMoveKey))
	{
		moveVec.y -= 1;
		move = true;
	}
	if (!move)
	{
		m_cursorMoveSpeed = 0.0f;
	}
	else
	{
		D3DXVec2Normalize(&moveVec, &moveVec);
		m_cursorMoveSpeed += m_cursorMoveMaxSpeed * 2.0f* g_pTimeManager->GetDeltaTime();
		m_cursorMoveSpeed = min(m_cursorMoveSpeed, m_cursorMoveMaxSpeed);
		moveVec *= m_cursorMoveSpeed * g_pTimeManager->GetDeltaTime();
		m_cursorPos += moveVec;
		SetCursorPosition(m_cursorPos);
	}
	m_cursorDefaultImage->SetPosition(m_cursorPos);
	m_cursorDefaultImage->Update();

	// 오브젝트 위치 설정
	m_objectToPlace->SetPosition(m_map->IndexToPos(m_map->PosToIndex(m_objectPos)));
}

void PlayerCursor::Render()
{
	if (!m_placed)
	{
		m_objectToPlace->RenderPreviewImage();
		m_cursorDefaultImage->Render();
	}
}

void PlayerCursor::Release()
{
	SAFE_DELETE(m_cursorDefaultImage);
	SAFE_DELETE(m_cursorOutOfBoundsImage);
}

void PlayerCursor::SetCursorPosition(D3DXVECTOR2 pos)
{
	m_cursorPos = pos;
	m_objectPos = m_cursorPos + D3DXVECTOR2(200, 40);
}				 