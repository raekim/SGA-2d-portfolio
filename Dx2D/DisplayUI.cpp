#include "stdafx.h"
#include "DisplayUI.h"


DisplayUI::DisplayUI()
{
}

DisplayUI::DisplayUI(Sprite * s)
{
	m_pSprite = s;
	this->Init();
}


DisplayUI::~DisplayUI()
{
	SAFE_DELETE(m_pSprite);
}

void DisplayUI::Init()
{
	m_displayDuration = 1.5f;
}

void DisplayUI::Update()
{
	if (m_isDisplaying)
	{
		m_pSprite->Update();

		m_displayDelta += g_pTimeManager->GetSystemDeltaTime();

		if (m_displayDelta >= m_displayDuration)
		{
			// UI 디스플레이가 끝나고, 시간의 흐름을 원래대로 되돌린다.
			m_isDisplaying = false;
			g_isPaused = false;
		}
	}
}

void DisplayUI::Render()
{
	if (m_isDisplaying)
	{
		m_pSprite->Render();
	}
}

void DisplayUI::Display(D3DXVECTOR2 pos)
{
	m_pos = pos;
	m_pSprite->SetPosition({pos.x + m_pSprite->GetWidth()*0.5f, pos.y + m_pSprite->GetHeight()*0.5f});
	m_isDisplaying = true;
	m_displayDelta = 0.0f;
	g_isPaused = true;	// system 델타 타임을 제외한 모든 시간을 멈춘다.
}
