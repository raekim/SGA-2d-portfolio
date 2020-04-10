#pragma once
#include "AABB.h"
#include "PlaceableObject.h"
class SpringPlatform : public PlaceableObject
{
	enum class STATE
	{
		READY = -1,
		Idle,
		Pushed,
		Springly,
		Max
	};
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	Animation<STATE>*		m_AABBSizeAnimation;
	Animation<STATE>*		m_animation;
	STATE					m_curState;
	D3DXVECTOR2				m_AABBHalfSize[6];
	Sprite*					m_previewImage;
	D3DXVECTOR2				m_positionOffset;
public:
	SpringPlatform();
	~SpringPlatform();

	virtual void Init() override;
	virtual void Update(vector<vector<PlaceableObject*>>& objList) override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	virtual void RenderPreviewImage() override;
};

