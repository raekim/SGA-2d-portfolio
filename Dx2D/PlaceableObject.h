#pragma once
class Player;
class Collider;
class Map;
class PlaceableObject
{
public:
	enum class collisionCheckDir
	{
		LEFT_WALL,
		RIGHT_WALL,
		CEILING,
		BOTTOM,
		JUST_COLLISION
	};

	D3DXVECTOR2				m_position;
	bool					m_flipped;
	Collider*				m_collider;
public:
	PlaceableObject();
	~PlaceableObject();

	virtual void Init() PURE;
	virtual void Update(vector<vector<PlaceableObject*>>& objList) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) PURE;

	void RegisterObjectCollider(Collider* collider, vector<vector<PlaceableObject*>>& objList);
	void SetPosition(D3DXVECTOR2 pos) { m_position = pos; };
	void SetFlip(bool val) { m_flipped = val; }

	virtual void SetPreviewImageColor(D3DXCOLOR color) PURE;
	virtual bool CanPlaceObject(int h, int w, Map* map) PURE;
	virtual void PlaceObject(int h, int w, Map* map) PURE;

	// 프리뷰 이미지 관련
	virtual void RenderPreviewImage() PURE;
};

