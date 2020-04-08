#include "stdafx.h"
#include "PlayScene.h"
#include "SimplePlatform.h"

PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
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

	g_pCamera->SetMapSize(GAMESCREEN_X, GAMESCREEN_Y);

	// �÷��̾� ����
	m_player1P = new Player;
	m_player1P->Init(L"Chicken-Sheet");
	m_player1P->SetJumpKey(VK_SPACE);
	m_player1P->SetLeftMoveKey(VK_LEFT);
	m_player1P->SetRightMoveKey(VK_RIGHT);
	m_player2P = new Player;
	m_player2P->Init(L"Chicken-Sheet-2P");
	m_player2P->SetJumpKey('Z');
	m_player2P->SetLeftMoveKey('F');
	m_player2P->SetRightMoveKey('H');

	// �÷��̾� Ŀ�� ����
	m_cursor1P = new PlayerCursor;
	m_cursor1P->Init(new Sprite(L"Chicken-Sheet", 7, 5, 7 * 4), new Sprite(L"Chicken-Sheet", 7, 5, 7 * 4 + 1));
	m_cursor1P->SetLeftMoveKey(VK_LEFT);
	m_cursor1P->SetRightMoveKey(VK_RIGHT);
	m_cursor1P->SetUpMoveKey(VK_UP);
	m_cursor1P->SetDownMoveKey(VK_DOWN);
	m_cursor1P->SetSelectKey(VK_SPACE);

	// �� ó���� ������忡�� ����
	SwitchToMapToolMode();
}

void PlayScene::Update()
{
	// ESC ������ ���α׷� ����
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0); // WM_QUIT �޽��� �߻�
	}

	// ���� ���(����/�÷���)�� ���� ������Ʈ
	switch (m_curMode)
	{
		case MODE::MAPTOOL_MODE:
			if (m_cursor1P->Update(m_placedObjects))
			{
				SwitchToPlayMode();
				break;
			}
			for (auto obj : m_placedObjects) obj->Update();
			break;
		case MODE::PLAY_MODE:
			// �÷��̾ ��� ������ �������� ��ȯ
			if (m_player1P->IsDead() && m_player2P->IsDead())
			{
				SwitchToMapToolMode();
				break;
			}
			for (auto obj : m_mapBlocks) obj->Update();
			m_player1P->Update(m_mapBlocks);
			m_player2P->Update(m_mapBlocks);
			for (auto obj : m_placedObjects) obj->Update();
			break;
	}

	g_pCamera->Update();
}

void PlayScene::Render()
{
	switch (m_curMode)
	{
	case MODE::MAPTOOL_MODE:
		m_mapBackground->Render();
		m_mapPaper->Render();
		m_mapForeground->Render();
		m_cursor1P->Render();

		for (auto obj : m_placedObjects) obj->Render();
		break;
	case MODE::PLAY_MODE:
		m_mapBackground->Render();
		m_mapForeground->Render();

		m_player1P->Render();
		m_player2P->Render();

		for (auto obj : m_placedObjects) obj->Render();
		break;
	}
}

void PlayScene::SwitchToMapToolMode()
{
	// ���� ���� �Ѿ��
	m_curMode = MODE::MAPTOOL_MODE;

	// ī�޶� ���� ����
	g_pCamera->SetEyeVal(-1.666f);
	g_pCamera->SetTarget(NULL);
	g_pCamera->SetPosition({ 0,0 });

	// Ŀ�� ����
	m_cursor1P->SetCursorPosition({ 800,800 });
	m_cursor1P->SetObjectToPlace(new SimplePlatform({ 25,25 }, { 0,0 }));
}

void PlayScene::SwitchToPlayMode()
{
	// �÷��� ���� �Ѿ��
	m_curMode = MODE::PLAY_MODE;

	// ī�޶� ���� ����
	g_pCamera->SetEyeVal(-1.0f);
	g_pCamera->SetTarget(m_player1P->GetPosition());

	// ĳ���� ����
	m_player1P->Revive({ 600.0f, 800.0f });
	m_player2P->Revive({ 650.0f, 800.0f });
}

void PlayScene::Release()
{
	SAFE_DELETE(m_mapBackground);
	SAFE_DELETE(m_mapPaper);
	SAFE_DELETE(m_mapForeground);

	SAFE_DELETE(m_player1P);
	SAFE_DELETE(m_player2P);
	SAFE_DELETE(m_cursor1P);
}
