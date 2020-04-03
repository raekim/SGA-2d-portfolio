#pragma once
#include "AABB.h"
#include "PlaceableObject.h"

class SimplePlatform : public PlaceableObject
{
	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	Sprite*					m_sprite;

public:
	enum class Platform_Type
	{
		SHORT_VERTICAL,
		SHORT_HORIZONTAL,
		MID_VERTICAL,
		MID_HORIZONTAL,
		LONG_VERTICAL,
		LONG_HORIZONTAL
	};
public:
	SimplePlatform(D3DXVECTOR2 AABBHalfSize, D3DXVECTOR2 pos);
	SimplePlatform(Platform_Type type, D3DXVECTOR2 pos);
	~SimplePlatform();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
};

