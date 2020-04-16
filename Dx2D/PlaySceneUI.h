#pragma once
class PlaySceneUI
{
	enum class SCOREBOARD_STATE
	{
		APPEARING,		// ������ ������
		SHOWING,		// ������ ���̴� ��
		DISAPPEARING	// ������ ������� ��
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

