#pragma once
#include "iGameNode.h"

class TitleScene : public iGameNode
{
private:
	Sprite*		m_pBackground;
	string		m_strTitle;
	float		m_fElapsedTime;
	bool		m_isRender;

	vector<pair<int, int>> m_vecPair;

public:
	TitleScene() {};
	~TitleScene() {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

