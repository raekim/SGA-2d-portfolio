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
	m_objectToPlace->SetPosition(IndexToPos(PosToIndex(m_objectPos)));
	m_objectToPlace->SetFlip(m_isFlipped);
}

void PlayerCursor::Init(Sprite * cursorDefaultImg, Sprite * cursorOutOfBoundsImg)
{
	m_cursorDefaultImage = cursorDefaultImg;
	m_cursorOutOfBoundsImage = cursorOutOfBoundsImg;

	m_cursorMoveMaxSpeed = 500.0f;
	m_cursorMoveSpeed = 0.0f;

	m_paperWidth = 2049;
	m_paperHeight = 1800;
	m_cellSize = 64.0f;

	m_zeroWidthPoint = (GAMESCREEN_X - m_paperWidth)*0.5f + m_cellSize * 0.5f;
	m_zeroHeightPoint = (GAMESCREEN_Y - m_paperHeight)*0.5f + m_cellSize * 0.5f;
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
	m_objectToPlace->SetPosition(IndexToPos(PosToIndex(m_objectPos)));
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

pair<int, int> PlayerCursor::PosToIndex(D3DXVECTOR2 pos)
{
	pair<int, int> res;

	// 오브젝트 배치 가능한 영역 안으로 clamp
	pos.x = min(pos.x, (GAMESCREEN_X + m_paperWidth)*0.5f);
	pos.x = max(pos.x, (GAMESCREEN_X - m_paperWidth)*0.5f);
	pos.y = min(pos.y, (GAMESCREEN_Y + m_paperHeight)*0.5f);
	pos.y = max(pos.y, (GAMESCREEN_Y - m_paperHeight)*0.5f);

	pos.x -= m_zeroWidthPoint;
	pos.y -= m_zeroHeightPoint;

	// 위치를 인덱스로 변환
	res.first = pos.x / m_cellSize;
	res.second = pos.y / m_cellSize;

	return res;
}

D3DXVECTOR2 PlayerCursor::IndexToPos(pair<int, int> index)
{
	D3DXVECTOR2 res;

	res.x = m_zeroWidthPoint + m_cellSize * index.first;
	res.y = m_zeroHeightPoint + m_cellSize * index.second;

	return res;
}
