#pragma once

#define MAP_WIDTH 16		// ���� Ÿ�� ����
#define MAP_HEIGHT 9		// ���� Ÿ�� ����
#define TILE_SIZE 120		// ���簢�� Ÿ���� �� �� ����

enum class TileType
{
	Empty,
	Block,
	// �浹 Ÿ�� �Ӹ� �ƴ϶� Ÿ���� �ܰ��� ���󼭵� enum ���� �߰�
	// ...
	Max
};

class Map : public iGameNode
{
	Rect*			m_rect;					// ���� �׸� �ӽ� �簢��
	TileType		m_Tiles[MAP_WIDTH][MAP_HEIGHT];
	vector<Sprite*> m_TilesSprites;
public:
	Map();
	~Map();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	// D3DXVECTOR2 Ÿ���� ��ǥ�� Ÿ�ϸ� �ε����� ��ȯ�ϴ� �Լ�
	POINT GetTilePointAtWorldPoint(D3DXVECTOR2 worldPoint);
	int GetTileXAtWorldPoint(D3DXVECTOR2 worldPoint);
	int GetTileYAtWorldPoint(D3DXVECTOR2 worldPoint);

	// Ư�� �ε����� Ÿ�ϸ��� D3DXVECTOR2 Ÿ���� ��ǥ�� ��ȯ�ϴ� �Լ� (Ÿ�� �� �߾��� ��ǥ ��ȯ)
	D3DXVECTOR2 GetWorldPointAtTile(int x, int y);
	D3DXVECTOR2 GetWorldPointAtTile(POINT point);

	// Ư�� �ε����� Ÿ�ϸ��� �𼭸� ��ġ�� ��ȯ�ϴ� �Լ�
	float GetTileTop(POINT point) { return GetWorldPointAtTile(point).y + TILE_SIZE*0.5f; }			// Ÿ���� �� y��ǥ
	float GetTileBottom(POINT point) { return GetWorldPointAtTile(point).y - TILE_SIZE * 0.5f; }	// Ÿ���� �Ʒ� y��ǥ
	float GetTileLeft(POINT point) { return GetWorldPointAtTile(point).x - TILE_SIZE * 0.5f; }		// Ÿ���� ���� x��ǥ
	float GetTileRight(POINT point) { return GetWorldPointAtTile(point).x + TILE_SIZE * 0.5f; }		// Ÿ���� ������ x��ǥ

	bool IsObstacle(int x, int y);
	bool IsEmpty(int x, int y);
	bool IsGround(int x, int y);
	TileType GetTileType(int x, int y);
};

