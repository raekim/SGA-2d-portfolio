#pragma once
#include "iGameNode.h"
class RenderTextureTest : public iGameNode
{
private:
	Sprite*		m_pBackground;
	Sprite*		m_pForeground;
	Sprite*		m_pMap;

	Circle*		m_pCircleBrush;
	float		m_fBrushRadius;

public:
	RenderTextureTest() {};
	~RenderTextureTest() {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

