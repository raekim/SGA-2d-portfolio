#include "stdafx.h"
#include "PlayerCursor.h"
#include "PlaceableObject.h"
#include "SimplePlatform.h"

PlayerCursor::PlayerCursor()
{
}


PlayerCursor::~PlayerCursor()
{
}

void PlayerCursor::Init(Sprite * cursorDefaultImg, Sprite * cursorOutOfBoundsImg)
{
	m_cursorDefaultImage = cursorDefaultImg;
	m_cursorOutOfBoundsImage = cursorOutOfBoundsImg;

	m_cursorMoveMaxSpeed = 500.0f;
	m_cursorMoveSpeed = 0.0f;

	m_paperWidth = 2049;
	m_paperHeight = 1800;
	m_cellSize = 64.285f;

	m_zeroWidthPoint = (GAMESCREEN_X - m_paperWidth)*0.5f + m_cellSize * 0.5f;
	m_zeroHeightPoint = (GAMESCREEN_Y - m_paperHeight)*0.5f + m_cellSize * 0.5f;
}

bool PlayerCursor::Update(vector<PlaceableObject*>& objList)
{
	MoveCursor();

	// 오브젝트 놓기
	if (g_pKeyManager->IsOnceKeyDown(m_selectKey))
	{
		objList.push_back(m_objectToPlace);
		return true;
	}
	return false;
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
	m_objectToPlace->SetPosition(m_objectPos);
	m_objectToPlace->Update();
}

void PlayerCursor::Render()
{
	m_objectToPlace->Render();
	m_cursorDefaultImage->Render();
}

void PlayerCursor::Release()
{
	SAFE_DELETE(m_cursorDefaultImage);
	SAFE_DELETE(m_cursorOutOfBoundsImage);
}

void PlayerCursor::SetCursorPosition(D3DXVECTOR2 pos)
{
	m_cursorPos = pos;
	m_objectPos = D3DXVECTOR2(m_zeroHeightPoint, m_zeroWidthPoint);// m_cursorPos + D3DXVECTOR2(180, 40);
}				 

