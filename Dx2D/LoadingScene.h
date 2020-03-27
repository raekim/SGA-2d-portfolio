#pragma once
#include "iGameNode.h"


class LoadingScene : public iGameNode
{
private:
	ProgressBar * m_pProgressBar;

public:
	LoadingScene() {};
	~LoadingScene() {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

