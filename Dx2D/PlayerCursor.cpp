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

	// Ŀ�� ��ġ ����
	m_cursorDefaultImage->SetPosition(m_cursorPos);
	m_cursorDefaultImage->Update();
	
	// ������Ʈ ������ �̹��� ��ġ ����
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
	
	// ���� ��ġ�� ������Ʈ�� ���� �� �ֳ� �˻�
	auto placeIndex = m_map->PosToIndex(m_objectPos);
	m_canPlaceObjectOnCurPos = m_objectToPlace->CanPlaceObject(placeIndex.second, placeIndex.first, m_map);

	// ������Ʈ flip �ϱ�
	if (g_pKeyManager->IsOnceKeyDown(m_flipKey))
	{
		m_isFlipped = !m_isFlipped;
		m_objectToPlace->SetFlip(m_isFlipped);
	}

	// ������Ʈ ����
	if (m_canPlaceObjectOnCurPos)
	{
		// ������Ʈ�� ���� �� �ִ� ��Ȳ
		m_objectToPlace->SetPreviewImageColor({ 1,1,1,1 });
		
		// select Ű�� ������ ���� ��ġ�� ������Ʈ�� ���´�
		if (g_pKeyManager->IsOnceKeyDown(m_selectKey))
		{
			m_objectToPlace->PlaceObject(placeIndex.second, placeIndex.first, m_map);
			m_objectToPlace->SetFlip(m_isFlipped);
			m_objectToPlace->Init();
			objList.push_back(m_objectToPlace);
			m_placed = true;
		}
	}
	else
	{
		// ������Ʈ�� ���� �� ���� ��Ȳ
		m_objectToPlace->SetPreviewImageColor({ 1,0,0,1 });
	}
	return m_placed;
}

void PlayerCursor::MoveCursor()
{
	// Ŀ�� �̵�
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

	// ������Ʈ ��ġ ����
	m_objectToPlace->SetPosition(m_map->IndexToPos(m_map->PosToIndex(m_objectPos)));
}

void PlayerCursor::Render()
{
	if (!m_placed)
	{
		// ������ �ϴ� ������Ʈ ����
		m_objectToPlace->RenderPreviewImage();

		// Ŀ�� ����
		if (m_canPlaceObjectOnCurPos)
		{
			// ������Ʈ ���� ����
			m_cursorDefaultImage->SetPosition(m_cursorPos);
			m_cursorDefaultImage->Update();
			m_cursorDefaultImage->Render();
		}
		else
		{
			// ������Ʈ ���� �Ұ���
			m_cursorOutOfBoundsImage->SetPosition(m_cursorPos);
			m_cursorOutOfBoundsImage->Update();
			m_cursorOutOfBoundsImage->Render();
		}
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