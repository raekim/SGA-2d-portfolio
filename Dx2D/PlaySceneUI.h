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
	SCOREBOARD_STATE	m_scoreBoardState;
	bool				m_showingScoreBoard;
	float				m_scoreBoardShowingTime;
	float				m_scoreBoardShowingTimeCount;
public:
	PlaySceneUI();
	~PlaySceneUI();

	void Init();
	void Update();
	void Render();
	void ShowScoreBoard(float showingTime = 1.0f);
};

