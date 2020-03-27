#pragma once
class DisplayUI
{
	float					m_displayDuration;
	float					m_displayDelta;
	D3DXVECTOR2				m_pos;
	Sprite*					m_pSprite;
	bool					m_isDisplaying;
	float					m_prevTimeScale;
public:
	DisplayUI();
	DisplayUI(Sprite* s);
	~DisplayUI();

	void Init();
	void Update();
	void Render();

	void Display(D3DXVECTOR2 pos);
	void SetDisplayDuration(float t) { m_displayDuration = t; }
};

