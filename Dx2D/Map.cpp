#include "stdafx.h"
#include "Map.h"
#include "SimplePlatform.h"
#include "GoalFlag.h"

Map::Map()
{
}


Map::~Map()
{
}

void Map::Init()
{
	m_paperWidth = 2049;
	m_paperHeight = 1800;
	m_cellSize = 64.0f;

	// (m_paperHeight)x(m_paperWidth) 크기의 2차원 bool 벡터 생성
	m_vecPaperCellMark = new vector<vector<bool>>(m_paperHeight, vector<bool>(m_paperWidth, false));

	// 오브젝트 종이 기준으로 (0,0)지점 (왼쪽 아래) 위치 초기화
	m_zeroWidthPoint = (GAMESCREEN_X - m_paperWidth)*0.5f + m_cellSize * 0.5f;
	m_zeroHeightPoint = (GAMESCREEN_Y - m_paperHeight)*0.5f + m_cellSize * 0.5f;

	// 배경 이미지 불러오기
	m_mapForeground = new Sprite(L"City-Foreground", 1, 1, 0);
	m_mapBackground = new Sprite(L"City-Background", 1, 1, 0);
	m_mapPaper = new Sprite(L"City-Paper", 1, 1, 0);

	m_mapForeground->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapBackground->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapPaper->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapForeground->Update();
	m_mapBackground->Update();
	m_mapPaper->Update();

	// 맵 지형 설정
	m_mapBlocks.push_back(new SimplePlatform({ 200.0f, 350.0f }, { 465.0f, 300.0f }));
	m_mapBlocks.push_back(new SimplePlatform({ 447.0f, 380.0f }, { GAMESCREEN_X - 653, 300.0f }));

	// 골인깃발 설정
	m_goalFlag = new GoalFlag;
	m_goalFlag->Init();
	m_goalFlag->SetPosition({ GAMESCREEN_X - 550, GAMESCREEN_Y*0.5f - 150 });
}

bool Map::GetCellStatus(int w, int h)
{
	if (w < 0 || w >= m_paperWidth) return false;
	if (h < 0 || h >= m_paperHeight) return false;

	return (*m_vecPaperCellMark)[h][w];
}

void Map::SetCellStatus(int w, int h, bool val)
{
	if (w < 0 || w >= m_paperWidth) return;
	if (h < 0 || h >= m_paperHeight) return;

	(*m_vecPaperCellMark)[h][w] = val;
}

pair<int, int> Map::PosToIndex(D3DXVECTOR2 pos)
{
	pair<int, int> res;

	// 오브젝트 배치 가능한 영역 안으로 clamp
	pos.x = min(pos.x, (GAMESCREEN_X + m_paperWidth)*0.5f);
	pos.x = max(pos.x, (GAMESCREEN_X - m_paperWidth)*0.5f);
	pos.y = min(pos.y, (GAMESCREEN_Y + m_paperHeight)*0.5f);
	pos.y = max(pos.y, (GAMESCREEN_Y - m_paperHeight)*0.5f);

	pos.x -= m_zeroWidthPoint;
	pos.y -= m_zeroHeightPoint;

	// 위치를 인덱스로 변환
	res.first = pos.x / m_cellSize;
	res.second = pos.y / m_cellSize;

	return res;
}

D3DXVECTOR2 Map::IndexToPos(pair<int, int> index)
{
	D3DXVECTOR2 res;

	res.x = m_zeroWidthPoint + m_cellSize * index.first;
	res.y = m_zeroHeightPoint + m_cellSize * index.second;

	return res;
}
