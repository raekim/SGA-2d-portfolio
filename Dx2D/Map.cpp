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

	// (m_paperHeight)x(m_paperWidth) ũ���� 2���� bool ���� ����
	m_vecPaperCellMark = new vector<vector<bool>>(m_paperHeight, vector<bool>(m_paperWidth, false));

	// �� �⺻ ���� ����
	for (int i = 0; i < 11; ++i)
	{
		this->SetCellStatus(i, 0, true);
		this->SetCellStatus(i, 1, true);
	}
	for (int i = 8; i <= 10; ++i)
	{
		this->SetCellStatus(i, 2, true);
	}
	for (int i = 0; i <= 9; ++i)
	{
		for (int j = 24; j <= 32; ++j)
			this->SetCellStatus(i, j, true);
	}
	for (int i = 10; i <= 11; ++i)
	{
		for (int j = 26; j <= 29; ++j)
			this->SetCellStatus(i, j, true);
	}

	// ������Ʈ ���� �������� (0,0)���� (���� �Ʒ�) ��ġ �ʱ�ȭ
	m_zeroWidthPoint = (GAMESCREEN_X - m_paperWidth)*0.5f + m_cellSize * 0.5f;
	m_zeroHeightPoint = (GAMESCREEN_Y - m_paperHeight)*0.5f + m_cellSize * 0.5f;

	// ��� �̹��� �ҷ�����
	m_mapForeground = new Sprite(L"City-Foreground", 1, 1, 0);
	m_mapBackground = new Sprite(L"City-Background", 1, 1, 0);
	m_mapPaper = new Sprite(L"City-Paper", 1, 1, 0);

	m_mapForeground->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapBackground->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapPaper->SetPosition(GAMESCREEN_X*0.5f, GAMESCREEN_Y*0.5f);
	m_mapForeground->Update();
	m_mapBackground->Update();
	m_mapPaper->Update();

	// �� ���� ����
	m_mapBlocks.push_back(new SimplePlatform({ 200.0f, 350.0f }, { 465.0f, 300.0f }));
	m_mapBlocks.push_back(new SimplePlatform({ 447.0f, 380.0f }, { GAMESCREEN_X - 653, 300.0f }));

	// ���α�� ����
	m_goalFlag = new GoalFlag;
	m_goalFlag->Init();
	m_goalFlag->SetPosition({ GAMESCREEN_X - 730, GAMESCREEN_Y*0.5f - 150 });
}

void Map::Update(vector<vector<PlaceableObject*>>& objList)
{
	// �� �� �ִ� ��ֹ��鿡 ���� ������Ʈ �� ȭ������� ĭ�� Register�Ѵ�
	for (auto obj : m_mapBlocks) obj->Update(objList);
	for (auto obj : m_placedObjects) obj->Update(objList);
	m_goalFlag->Update(objList);
}

void Map::RenderPlayMode()
{
	// �� ��׶��� �� ���α�� ����
	m_mapBackground->Render();
	m_goalFlag->Render();
	m_mapForeground->Render();

	// �� ���� ��ֹ� ����
	for (auto obj : m_placedObjects) obj->Render();
}

void Map::RenderMapToolMode()
{
	// ������� �� ����
	m_mapBackground->Render();
	m_mapPaper->Render();
	m_goalFlag->RenderPreviewImage();
	m_mapForeground->Render();

	// �� ���� ��ֹ� ������ ���� ����
	for (auto obj : m_placedObjects) obj->RenderPreviewImage();
}

bool Map::GetCellStatus(int h, int w)
{
	if (w < 0 || w >= m_paperWidth) return false;
	if (h < 0 || h >= m_paperHeight) return false;

	return (*m_vecPaperCellMark)[h][w];
}

void Map::SetCellStatus(int h, int w, bool val)
{
	if (w < 0 || w >= m_paperWidth) return;
	if (h < 0 || h >= m_paperHeight) return;

	(*m_vecPaperCellMark)[h][w] = val;
}

pair<int, int> Map::PosToIndex(D3DXVECTOR2 pos)
{
	pair<int, int> res;

	// ������Ʈ ��ġ ������ ���� ������ clamp
	pos.x = min(pos.x, (GAMESCREEN_X + m_paperWidth)*0.5f);
	pos.x = max(pos.x, (GAMESCREEN_X - m_paperWidth)*0.5f);
	pos.y = min(pos.y, (GAMESCREEN_Y + m_paperHeight)*0.5f);
	pos.y = max(pos.y, (GAMESCREEN_Y - m_paperHeight)*0.5f);

	pos.x -= m_zeroWidthPoint;
	pos.y -= m_zeroHeightPoint;

	// ��ġ�� �ε����� ��ȯ
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

void Map::Release()
{
	SAFE_DELETE(m_mapBackground);
	SAFE_DELETE(m_mapPaper);
	SAFE_DELETE(m_mapForeground);
	m_goalFlag->Release();
}