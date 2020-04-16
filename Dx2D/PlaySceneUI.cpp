#include "stdafx.h"
#include "PlaySceneUI.h"


PlaySceneUI::PlaySceneUI()
{
	m_scoreBoard = new Sprite(L"ScoreBoard", 1, 1, 0);
	m_scoreBoard->SetSize(1.7f, 1.7f);
	m_showingScoreBoard = false;

	m_socreCheckMark = new Sprite(L"scoreCheckMark", 1, 1, 0);
	m_socreCheckMark->SetSize(0.5f, 0.5f);
	m_socreCheckMark->SetColor({ 1,0,0,1 });

	m_scoreMarkOffset1P = D3DXVECTOR2(-30, 190);
	m_scoreMarkOffset2P = D3DXVECTOR2(-30, -230);
	m_scoreMarkHorizontalOffset = D3DXVECTOR2(113, 0);
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
		m_socreCheckMark->SetPosition(m_scoreBoard->GetPosition());
	}
}

void PlaySceneUI::Render()
{
	if (m_showingScoreBoard)
	{
		m_scoreBoard->Render();

		for (int i = 0; i < m_score1P; ++i)
		{
			m_socreCheckMark->SetPosition(m_scoreBoard->GetPosition() + m_scoreMarkOffset1P + m_scoreMarkHorizontalOffset*i);
			m_socreCheckMark->Update();
			m_socreCheckMark->Render();
		}

		for (int i = 0; i < m_score2P; ++i)
		{
			m_socreCheckMark->SetPosition(m_scoreBoard->GetPosition() + m_scoreMarkOffset2P + m_scoreMarkHorizontalOffset * i);
			m_socreCheckMark->Update();
			m_socreCheckMark->Render();
		}
	}
}

void PlaySceneUI::ShowScoreBoard(int redScore, int blueScore, float showingTime)
{
	if (m_showingScoreBoard == false)
	{
		m_score1P = redScore;
		m_score2P = blueScore;
		m_scoreBoardShowingTime = showingTime;
		m_scoreBoardShowingTimeCount = 0.0f;
		m_showingScoreBoard = true;
		m_scoreBoard->SetPosition({ GAMESCREEN_X*0.5f, -m_scoreBoard->GetHeight()*0.5f });
		m_scoreBoardState = SCOREBOARD_STATE::APPEARING;
	}
}
