#pragma once
class PlaySceneUI
{
	enum class SCOREBOARD_STATE
	{
		APPEARING,		// 점수판 등장중
		SHOWING,		// 점수판 보이는 중
		DISAPPEARING	// 점수판 사라지는 중
	};

	Sprite*				m_scoreBoard;
	Sprite*				m_socreCheckMark;
	SCOREBOARD_STATE	m_scoreBoardState;
	bool				m_showingScoreBoard;
	float				m_scoreBoardShowingTime;
	float				m_scoreBoardShowingTimeCount;
	D3DXVECTOR2			m_scoreMarkOffset1P;				// 1P 점수 체크마크 오프셋
	D3DXVECTOR2			m_scoreMarkOffset2P;				// 2P 점수 체크마크 오프셋
	D3DXVECTOR2			m_scoreMarkHorizontalOffset;		// 점수 체크마크 가로 오프셋

	int					m_score1P, m_score2P;
public:
	PlaySceneUI();
	~PlaySceneUI();

	void Init();
	void Update();
	void Render();
	void ShowScoreBoard(int redScore, int blueScore, float showingTime = 1.0f);
};

