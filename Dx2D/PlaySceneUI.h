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
	Sprite*				m_socreCheckMark;
	SCOREBOARD_STATE	m_scoreBoardState;
	bool				m_showingScoreBoard;
	float				m_scoreBoardShowingTime;
	float				m_scoreBoardShowingTimeCount;
	D3DXVECTOR2			m_scoreMarkOffset1P;				// 1P ���� üũ��ũ ������
	D3DXVECTOR2			m_scoreMarkOffset2P;				// 2P ���� üũ��ũ ������
	D3DXVECTOR2			m_scoreMarkHorizontalOffset;		// ���� üũ��ũ ���� ������

	int					m_score1P, m_score2P;
public:
	PlaySceneUI();
	~PlaySceneUI();

	void Init();
	void Update();
	void Render();
	void ShowScoreBoard(int redScore, int blueScore, float showingTime = 1.0f);
};

