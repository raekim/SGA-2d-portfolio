#pragma once
class Player;
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
	PlaceableObject();
	~PlaceableObject();

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) PURE;
};

