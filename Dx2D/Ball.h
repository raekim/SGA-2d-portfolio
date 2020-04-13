#pragma once
#include "PlaceableObject.h"
class Ball : public PlaceableObject
{
	D3DXVECTOR2				m_speed;
	float					m_xSpeedBound; // 발사된 공의 x 스피드의 절대값이 점점 감소하다가 이 밑으로는 감소하지 않는 값
	Sprite*					m_ballSprite;
	bool					m_enabled;
public:
	Ball();
	~Ball();

	virtual void Init() override;
	virtual void Update(vector<vector<PlaceableObject*>>& objList) override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	virtual void RenderPreviewImage() override {};

	void SetEnabled(bool val) { m_enabled = val; }
	bool GetEnabled() { return m_enabled; }
	void SetSpeed(D3DXVECTOR2 speed) { m_speed = speed; }
};

