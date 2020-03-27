#pragma once

#define MAP_WIDTH 16		// 가로 타일 갯수
#define MAP_HEIGHT 9		// 세로 타일 갯수
#define TILE_SIZE 120		// 정사각형 타일의 한 변 길이

enum class TileType
{
	Empty,
	Block,
	// 충돌 타입 뿐만 아니라 타일의 외관에 따라서도 enum 종류 추가
	// ...
	Max
};

class Map : public iGameNode
{
	Rect*			m_rect;					// 맵을 그릴 임시 사각형
	TileType		m_Tiles[MAP_WIDTH][MAP_HEIGHT];
	vector<Sprite*> m_TilesSprites;
public:
	Map();
	~Map();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	// D3DXVECTOR2 타입의 좌표를 타일맵 인덱스로 변환하는 함수
	POINT GetTilePointAtWorldPoint(D3DXVECTOR2 worldPoint);
	int GetTileXAtWorldPoint(D3DXVECTOR2 worldPoint);
	int GetTileYAtWorldPoint(D3DXVECTOR2 worldPoint);

	// 특정 인덱스의 타일맵을 D3DXVECTOR2 타입의 좌표로 변환하는 함수 (타일 정 중앙의 좌표 반환)
	D3DXVECTOR2 GetWorldPointAtTile(int x, int y);
	D3DXVECTOR2 GetWorldPointAtTile(POINT point);

	// 특정 인덱스의 타일맵의 모서리 위치를 반환하는 함수
	float GetTileTop(POINT point) { return GetWorldPointAtTile(point).y + TILE_SIZE*0.5f; }			// 타일의 위 y좌표
	float GetTileBottom(POINT point) { return GetWorldPointAtTile(point).y - TILE_SIZE * 0.5f; }	// 타일의 아래 y좌표
	float GetTileLeft(POINT point) { return GetWorldPointAtTile(point).x - TILE_SIZE * 0.5f; }		// 타일의 왼쪽 x좌표
	float GetTileRight(POINT point) { return GetWorldPointAtTile(point).x + TILE_SIZE * 0.5f; }		// 타일의 오른쪽 x좌표

	bool IsObstacle(int x, int y);
	bool IsEmpty(int x, int y);
	bool IsGround(int x, int y);
	TileType GetTileType(int x, int y);
};

