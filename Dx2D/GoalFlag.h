#pragma once
#include "PlaceableObject.h"
class GoalFlag : public PlaceableObject
{
	enum class ANIM_STATE
	{
		READY = -1,
		IDLE
	};

	Animation<ANIM_STATE>*	m_pAnimation;
	Sprite*					m_poleSprite;
	D3DXVECTOR2				m_poleOffset;
public:
	GoalFlag();
	~GoalFlag();

	virtual void Init() override;
	virtual void Update(vector<vector<PlaceableObject*>>& objList) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;

	// 프리뷰 이미지 관련
	virtual void RenderPreviewImage() override;
};

