#include "stdafx.h"
#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

void Map::Init()
{
	m_rect = new Rect;
	m_rect->Init();
	m_rect->SetSize({ 120.0f, 120.0f });
	m_rect->SetDraw(true);
	m_rect->SetColor({ 0,0,1,1 });

	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			m_Tiles[x][y] = TileType::Empty;
		}
	}

	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		m_Tiles[x][0] = TileType::Block;
	}

	m_Tiles[3][2] = TileType::Block;
	m_Tiles[4][2] = TileType::Block;
	m_Tiles[5][2] = TileType::Block;
	m_Tiles[4][3] = TileType::Block;
	m_Tiles[3][4] = TileType::Block;

	m_Tiles[10][2] = TileType::Block;
	m_Tiles[11][2] = TileType::Block;
	m_Tiles[12][2] = TileType::Block;
	m_Tiles[12][3] = TileType::Block;
	m_Tiles[12][4] = TileType::Block;
	m_Tiles[12][5] = TileType::Block;
	m_Tiles[12][6] = TileType::Block;

	m_Tiles[9][2] = TileType::Block;
	m_Tiles[9][3] = TileType::Block;
	m_Tiles[9][4] = TileType::Block;
	m_Tiles[9][5] = TileType::Block;
	m_Tiles[9][6] = TileType::Block;


}

void Map::Update()
{
}

void Map::Render()
{
	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			if (m_Tiles[x][y] == TileType::Block)
			{
				m_rect->SetPosition(GetWorldPointAtTile(x, y));
				m_rect->Update();
				m_rect->Render();
			}
		}
	}
}

void Map::Release()
{
	SAFE_DELETE(m_rect);
}

POINT Map::GetTilePointAtWorldPoint(D3DXVECTOR2 worldPoint)
{
	return { (int)worldPoint.x / TILE_SIZE, (int)worldPoint.y / TILE_SIZE };
}

int Map::GetTileXAtWorldPoint(D3DXVECTOR2 worldPoint)
{
	return (int)worldPoint.x / TILE_SIZE;
}

int Map::GetTileYAtWorldPoint(D3DXVECTOR2 worldPoint)
{
	return (int)worldPoint.y / TILE_SIZE;
}

D3DXVECTOR2 Map::GetWorldPointAtTile(int x, int y)
{
	return { x*TILE_SIZE + TILE_SIZE * 0.5f, y*TILE_SIZE + TILE_SIZE * 0.5f };
}

D3DXVECTOR2 Map::GetWorldPointAtTile(POINT point)
{
	return{ point.x*TILE_SIZE + TILE_SIZE*0.5f, point.y*TILE_SIZE + TILE_SIZE*0.5f };
}

bool Map::IsObstacle(int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH ||
		y < 0 || y >= MAP_HEIGHT)
	{
		return true;
	}
	return (m_Tiles[x][y] == TileType::Block);
}

bool Map::IsEmpty(int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH ||
		y < 0 || y >= MAP_HEIGHT)
	{
		return false;
	}
	return (m_Tiles[x][y] == TileType::Empty);
}

bool Map::IsGround(int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH ||
		y < 0 || y >= MAP_HEIGHT)
	{
		return false;
	}
	return (m_Tiles[x][y] == TileType::Block);
}

TileType Map::GetTileType(int x, int y)
{
	// 인덱스가 범위를 벗어나면 블록으로 본다
	if (x < 0 || x >= MAP_WIDTH ||
		y < 0 || y >= MAP_HEIGHT)
	{
		return TileType::Block;
	}
	return m_Tiles[x][y];
}
