#pragma once
class Player;
class PlaceableObject
{
private:
	Sprite*					m_previewImg;		// 맵툴모드에서 보이는 이미지
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
public:
	PlaceableObject();
	~PlaceableObject();

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual bool handleCollision(D3DXVECTOR2 pos, Player* player, collisionCheckDir dir) PURE;

	void SetPosition(D3DXVECTOR2 pos) { m_position = pos; };
	Sprite* const GetPreviewImage() { return m_previewImg; }
	void SetPreviewImage(Sprite* img) { m_previewImg = img; }
	void SetFlip(bool val) { m_flipped = val; }

	// 프리뷰 이미지 관련
	void RenderPreviewImage();
};

