#pragma once
#include "AABB.h"
#include "PlaceableObject.h"

class SimplePlatform : public PlaceableObject
{
public:
	enum class Platform_Type
	{
		SHORT_VERTICAL,
		SHORT_HORIZONTAL,
		MID_VERTICAL,
		MID_HORIZONTAL,
		Max
	};
private:
	D3DXVECTOR3				m_rotation;
	//AABB*					m_AABB;
	Sprite*					m_sprite;
	D3DXVECTOR2				m_positionOffset;
	Platform_Type			m_platformType;
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

	virtual void SetPreviewImageColor(D3DXCOLOR color) override;
	virtual bool CanPlaceObject(int h, int w, Map* map) override;
	virtual void PlaceObject(int h, int w, Map* map) override;
};

