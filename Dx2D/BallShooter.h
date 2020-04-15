#pragma once
#include "AABB.h"
#include "PlaceableObject.h"
#include "CircleCollider.h"
#include "Ball.h"

class BallShooter : public PlaceableObject
{
	D3DXVECTOR3				m_rotation;
	AABB*					m_AABB;
	list<Ball*>				m_enabledBalls;				// 활성화되어 업데이트와 렌더 대상인 Ball들
	list<Ball*>				m_disabledBalls;			// 비활성화되어있는 오브젝트 풀 Ball
	D3DXVECTOR2				m_shootStartSpeed;			// 최초 발사 스피드
	D3DXVECTOR2				m_shootStartPoint;			// 발사 시작 지점
	float					m_shootDelay;				// 연속 발사 소요시간
	float					m_shootDelayCount;			// 연속 발사를 위해 카운트하는 시간

	Sprite*					m_machineSprite;

	D3DXVECTOR2				m_ballOffset;				// 공 이미지 offset
	D3DXVECTOR2				m_ballRotationOffest;		// 공 회전 중심점 offset
	D3DXVECTOR2				m_machineOffset;

public:
	BallShooter();
	~BallShooter();

	virtual void Init() override;
	virtual void Update(vector<vector<PlaceableObject*>>& objList) override;
	virtual void Render() override;
	virtual void Release() override;

	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) override;
	virtual void RenderPreviewImage() override;

	virtual void SetPreviewImageColor(D3DXCOLOR color) override;
	virtual bool CanPlaceObject(int h, int w, Map* map) override;
	virtual void PlaceObject(int h, int w, Map* map) override;
};

