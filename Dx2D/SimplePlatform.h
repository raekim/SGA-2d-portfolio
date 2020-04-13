#pragma once
#include "AABB.h"
#include "PlaceableObject.h"

class SimplePlatform : public PlaceableObject
{
	D3DXVECTOR3				m_rotation;
	//AABB*					m_AABB;
	Sprite*					m_sprite;
	D3DXVECTOR2				m_positionOffset;
public:
	enum class Platform_Type
	{
		SHORT_VERTICAL,
		SHORT_HORIZONTAL,
		MID_VERTICAL,
		MID_HORIZONTAL,
		Max
	};
public:
	SimplePlatform() {};
	SimplePlatform(D3DXVECTOR2 AABBHalfSize, D3DXVECTOR2 pos);
	SimplePlatform(Platform_Type type);
	~SimplePlatform();

	virtual void Init() override;
	virtual void Update(vector<vector<PlaceableObject*>>& objList) override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	virtual void RenderPreviewImage();
};

