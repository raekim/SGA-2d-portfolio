#pragma once
#include "AABB.h"
#include "PlaceableObject.h"

class SpinWheel : public PlaceableObject
{
	D3DXVECTOR2				m_position;
	D3DXVECTOR3				m_wheelRotation;

	float					m_barRotationAmount;
	float					m_barRoatationSecond;
	float					m_barRotationDelta;
	float					m_wheelRotationAmount;
	float					m_wheelRoatationSecond;
	float					m_wheelRotationDelta;

	AABB*					m_AABB;
	Sprite*					m_blockSprite;
	Sprite*					m_barSprite;
	Sprite*					m_wheelSprite;
public:
	SpinWheel(D3DXVECTOR2 pos);
	~SpinWheel();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
};

