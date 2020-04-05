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
	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	Animation<STATE>*		m_AABBSizeAnimation;
	Animation<STATE>*		m_animation;
	STATE					m_curState;
	D3DXVECTOR2				m_AABBHalfSize[6];
public:
	SpringPlatform(D3DXVECTOR2 pos);
	~SpringPlatform();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
};

