#include "stdafx.h"
#include "PlaySceneUI.h"


PlaySceneUI::PlaySceneUI()
{
	m_scoreBoard = new Sprite(L"ScoreBoard", 1, 1, 0);
	m_scoreBoard->SetSize(1.7f, 1.7f);
	m_showingScoreBoard = false;
}


PlaySceneUI::~PlaySceneUI()
{
}

void PlaySceneUI::Init()
{
}

void PlaySceneUI::Update()
{
	float moveSpeed = 3.0f;

	if (m_showingScoreBoard)
	{
		switch (m_scoreBoardState)
		{
		case  SCOREBOARD_STATE::APPEARING:
			if (fabs(m_scoreBoard->GetPosition().x - GAMESCREEN_X * 0.5f) <= 0.01f &&
				fabs(m_scoreBoard->GetPosition().y - GAMESCREEN_Y * 0.5f) <= 0.01f)
			{
				m_scoreBoardState = SCOREBOARD_STATE::SHOWING;
				break;
			}
			m_scoreBoard->SetPosition(m_scoreBoard->GetPosition() +
				(D3DXVECTOR2(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f) - m_scoreBoard->GetPosition())*g_pTimeManager->GetDeltaTime()*moveSpeed);
			break;
		case  SCOREBOARD_STATE::SHOWING:
			if (m_scoreBoardShowingTimeCount >= m_scoreBoardShowingTime)
			{
				m_scoreBoardState = SCOREBOARD_STATE::DISAPPEARING;
				break;
			}
			else
			{
				m_scoreBoardShowingTimeCount += g_pTimeManager->GetDeltaTime();
			}
			break;
		case  SCOREBOARD_STATE::DISAPPEARING:
			if (fabs(m_scoreBoard->GetPosition().x - GAMESCREEN_X * 0.5f) <= 0.01f &&
				fabs(m_scoreBoard->GetPosition().y - (-m_scoreBoard->GetHeight()*0.5f)) <= 0.01f)
			{
				m_showingScoreBoard = false;
				break;
			}
			m_scoreBoard->SetPosition(m_scoreBoard->GetPosition() +
				(D3DXVECTOR2(GAMESCREEN_X*0.5f, -m_scoreBoard->GetHeight()*0.5f) - m_scoreBoard->GetPosition())*g_pTimeManager->GetDeltaTime()*moveSpeed);
			break;
		}
		
		m_scoreBoard->Update();
	}
}

void PlaySceneUI::Render()
{
	if (m_showingScoreBoard)
	{
		m_scoreBoard->Render();
	}
}

void PlaySceneUI::ShowScoreBoard(float showingTime)
{
	if (m_showingScoreBoard == false)
	{
		m_scoreBoardShowingTime = showingTime;
		m_scoreBoardShowingTimeCount = 0.0f;
		m_showingScoreBoard = true;
		m_scoreBoard->SetPosition({ GAMESCREEN_X*0.5f, -m_scoreBoard->GetHeight()*0.5f });
		m_scoreBoardState = SCOREBOARD_STATE::APPEARING;
	}
}
