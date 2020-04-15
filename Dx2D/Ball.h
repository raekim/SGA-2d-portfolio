#pragma once
#include "PlaceableObject.h"
class Ball : public PlaceableObject
{
	D3DXVECTOR2				m_speed;
	float					m_xSpeedBound; // �߻�� ���� x ���ǵ��� ���밪�� ���� �����ϴٰ� �� �����δ� �������� �ʴ� ��
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

	virtual void SetPreviewImageColor(D3DXCOLOR color) override {};
	virtual bool CanPlaceObject(int h, int w, Map* map) override { return false; }
	virtual void PlaceObject(int h, int w, Map* map) override {};

	void SetEnabled(bool val) { m_enabled = val; }
	bool GetEnabled() { return m_enabled; }
	void SetSpeed(D3DXVECTOR2 speed) { m_speed = speed; }
};

